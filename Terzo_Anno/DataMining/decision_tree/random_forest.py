import numpy as np
from decision_tree import DecisionTree


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
