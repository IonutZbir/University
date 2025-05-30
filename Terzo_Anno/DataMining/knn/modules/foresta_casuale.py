import numpy as np
from graphviz import Digraph

class DecisionTree(object):
    def __init__(
        self, max_depth=3, min_size=1, criterion="gini", num_feats=None, random_state=0
    ):
        impurity_funcs = {"gini": self._gini, "entropy": self._entropy}

        self.max_depth = max_depth
        self.min_size = min_size
        self.tree = None

        self._impurity_fun = impurity_funcs[criterion]

        self._num_feats = num_feats
        self._random_state = random_state

        # indici delle features usate, in caso = None, tutte le features
        self._feature_indxs = None
        
        self.importance = {}
        

    def fit(self, X, y):
        """Costruisce l'albero di decisione"""
        y = np.array(y).reshape(
            -1, 1
        )  
        # anziché un vettore, è una matrice ad una colonna per tutte le righe che servono

        if self._num_feats != None and self._num_feats < X.shape[1]:
            rng = np.random.default_rng(seed=self._random_state)
            
            # indici delle features usate scelti randomicamente senza reinserimento
            self._feature_indxs = rng.choice(
                np.arange(X.shape[1]), self._num_feats, replace=False
            )
        else:
            self._feature_indxs = np.arange(X.shape[1])

        """
        Il dataset contiene sia X che y impilati verticalmente, questa è 
        la soluzione più conveniente per semplificare le operazioni
        di filtro delle righe che porterà alle suddivisioni del dataset che
        definiranno i nodi dell'albero
        """

        dataset = np.hstack((X, y))  # Concatenazione orizzontale
        self.tree = self._build_tree(dataset, 1)

    def _info_gain(self, dataset, groups):
        nl, nr = groups[0].shape[0], groups[1].shape[0]
        n = nl + nr
        ig = (
            self._impurity_fun(dataset)
            - self._impurity_fun(groups[0]) * nl / n
            - self._impurity_fun(groups[1]) * nr / n
        )
        return ig

    def _entropy(self, dataset):
        labs, occur = np.unique(dataset[:, -1], return_counts=True)
        score = 0
        for i, _ in enumerate(labs):
            proportion = occur[i] / dataset.shape[0]
            score += proportion * np.log2(proportion)
        return -score

    def _gini(self, dataset):
        labs, occur = np.unique(dataset[:, -1], return_counts=True)
        score = 0
        for i, _ in enumerate(labs):
            proportion = occur[i] / dataset.shape[0]
            score += proportion**2
        return 1 - score

    def _split_dataset(self, index, value, dataset):
        """Divide il dataset in due gruppi in base al confronto della caratteristica
        index con value"""
        mask = dataset[:, index] < value # crea un vettore booleano `mask` dove mask[i]
        left, right = dataset[mask], dataset[~mask]

        return left, right

    def _get_best_split(self, dataset):
        """Trova la feature (colonna di dataset) sulla quale esiste un valore tale che
        massimizza il guadagno informativo su tutte le possibili suddivisioni ottenibili usando
        tutte le possibili caratteristiche.

        Quindi per ogni caratteristica index e per ogni esempio row, si divide il dataset
        in base al test x[index] < row[index] e se ne calcola  il guadagno informativo.
        Si sceglie index e row[index] in modo da massimizzare questo valore
        """
        best_index, best_value, best_score, best_groups = (
            None,
            None,
            float("-inf"),
            None,
        )
        for index in self._feature_indxs: # per ogni feature usata
            for row in dataset:
                groups = self._split_dataset(index, row[index], dataset)
                ig = self._info_gain(dataset, groups)
                if ig > best_score:
                    best_index, best_value, best_score, best_groups = (
                        index,
                        row[index],
                        ig,
                        groups,
                    )

        # ritorna un nodo
        return {"index": best_index, "value": best_value, "groups": best_groups}

    def _create_leaf(self, group):
        """Crea un nodo foglia con la classe più comune"""
        values, counts = np.unique(group[:, -1], return_counts=True)
        return values[np.argmax(counts)]

    def _split(self, node, depth):
        """Cresce l'albero ricorsivamente"""
        left, right = node["groups"]
        # del node['groups']

        # Se uno dei gruppi è vuoto, assegniamo una foglia
        if left.size == 0 or right.size == 0:
            node["left"] = node["right"] = self._create_leaf(np.vstack((left, right)))
            return

        # Fermiamo la crescita se abbiamo raggiunto la profondità massima
        if depth >= self.max_depth:
            node["left"], node["right"] = self._create_leaf(left), self._create_leaf(
                right
            )
            return

        # Se il gruppo sinistro è troppo piccolo, creiamo una foglia
        if len(left) <= self.min_size:
            node["left"] = self._create_leaf(left)
        else:
            node["left"] = self._get_best_split(left)
            self._split(node["left"], depth + 1)

        # Se il gruppo destro è troppo piccolo, creiamo una foglia
        if len(right) <= self.min_size:
            node["right"] = self._create_leaf(right)
        else:
            node["right"] = self._get_best_split(right)
            self._split(node["right"], depth + 1)
        
        # si calcola l'importanza per ogni nodo
        
        indx = int(node["index"])
        val = float(node["value"])
        
        temp = self.importance.get(indx, 0)
        self.importance[indx] = temp + val

    def _build_tree(self, dataset, depth):
        """Costruisce l'albero a partire dai dati"""
        root = self._get_best_split(dataset)
        
        self._split(root, depth)
        return root

    def _is_leaf(self, node):
        return not isinstance(node, dict)

    def _predict_example(self, node, row):
        """Predice il valore di una singola riga"""
        if row[node["index"]] < node["value"]:
            if self._is_leaf(node["left"]):
                return node["left"]
            else:
                return self._predict_example(node["left"], row)

        else:
            if self._is_leaf(node["right"]):
                return node["right"]
            else:
                return self._predict_example(node["right"], row)

    def predict(self, row):
        """Predice la classe di una singola riga"""
        return self._predict_example(self.tree, row)

    def predict_batch(self, X):
        """Predice su un intero dataset"""
        return [self.predict(row) for row in X]

    def draw_tree(self):
        self.the_tree = Digraph()

        def add_nodes_edges(node, parent_id=None, edge_lab="SI"):
            if node is None:
                return

            # Se foglia (intero)
            if self._is_leaf(node):
                node_id = str(id(node))
                self.the_tree.node(node_id, str(node))
                if parent_id:
                    self.the_tree.edge(parent_id, node_id, edge_lab)
                return

            # Nodo interno
            node_id = str(id(node))
            label = f"f_{str(node.get('index',''))} < {str(node.get('value', ''))}"
            self.the_tree.node(node_id, label)

            if parent_id:
                self.the_tree.edge(parent_id, node_id, edge_lab)

            add_nodes_edges(node.get("left"), node_id, "SI")
            add_nodes_edges(node.get("right"), node_id, "NO")

        add_nodes_edges(self.tree)

    def show_tree(self):
        self.draw_tree()
        return self.the_tree

def mode(a):
    """
    parametro: a, un array-like

    return: l'elemento più frequente ed il numero di occorrenze

    """

    itms, cnts = np.unique(np.array(a), return_counts=True)

    return itms[np.argmax(cnts)], max(cnts)


class RandomForest(object):
    def __init__(
        self,
        n_trees=3,
        max_samples=None,
        max_feat_func=np.sqrt,
        max_depth=3,
        min_size=1,
        criterion="gini",
        random_state=0,
    ):

        self._n_trees = n_trees
        self._max_samples = max_samples
        self._max_feat_func = max_feat_func

        self._random_state = random_state

        self.max_depth = max_depth
        self.min_size = min_size
        self._impurity_fun = criterion

        self.trees = []
        self._used_rows = None  # struttura usata per valutazione oob
        self._importance = {}

    def fit(self, X, y):
        # Numero di caratteristiche calcolate come funzione del numero di colonne di X
        num_feats = int(self._max_feat_func(X.shape[1]))
        rng = np.random.default_rng(seed=self._random_state)

        self._used_rows = np.zeros((X.shape[0], self._n_trees), dtype=bool)
        # used_rows[i,t] vale True se la riga i è stata usata per addestrare l'albero t

        if self._max_samples == None:
            self._max_samples = X.shape[0]

        for i in range(self._n_trees):
            rnd_rows = np.unique(
                rng.choice(np.arange(X.shape[0]), self._max_samples, replace=True)
            )
            self._used_rows[rnd_rows, i] = True  # righe rnd_rows usate per albero i
            tree = DecisionTree(
                max_depth=self.max_depth,
                min_size=self.min_size,
                criterion=self._impurity_fun,
                num_feats=num_feats,
                random_state=i,
            )

            Xf = X[rnd_rows, :]
            yf = y[rnd_rows]

            tree.fit(Xf, yf)
            self.trees.append(tree)
            
            for key in tree.importance:            
                temp = self._importance.get(key, 0)
                self._importance[key] = temp + tree.importance[key]
        
        s = sum(list(self._importance.values()))
        for key in self._importance:
            self._importance[key] = self._importance[key] / s
            
            # print(f"Importance albero {i}: {tree.importance}")

        self._oob_valutation(X, y)

    def predict(self, x):
        predictions = np.empty(self._n_trees, dtype=object)

        for i in range(self._n_trees):
            predictions[i] = self.trees[i].predict(x)

        return mode(predictions)

    def _oob_valutation(self, X, y):
        """
        ogni esempio verrà utilizzato per valutare le prestazioni degli alberi di cui era out-of-bag
        """

        successes, n = (
            0,
            0,
        )  # numero di successi e numero di esperimenti (esempi oob almeno una volta)

        for i in range(X.shape[0]):
            xi, yi = X[i], y[i]

            predictions_xi = []

            for j in range(self._n_trees):
                if not self._used_rows[i][j]:  # xi non è stato usato per l'albero i
                    predictions_xi.append(self.trees[j].predict(xi))

            if predictions_xi != []:
                outcome, _ = mode(predictions_xi)
                successes += 1 if outcome == yi else 0
                n += 1

        self._oob_accuracy = successes / n

    def get_accuracy(self):
        return self._oob_accuracy
    
    def get_importance(self):
        return self._importance
            