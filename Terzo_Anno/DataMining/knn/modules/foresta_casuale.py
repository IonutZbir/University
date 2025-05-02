#!/usr/bin/env python
# coding: utf-8

# # Foreste casuali
# 
# Il modello utilizza un insieme di $k$ alberi decisionali addestrati separatamente. Per classificare, ognuno dei $k$ alberi assegna una etichetta; l'etichetta finale sarà quella più frequente. Se si fa in modo che tra gli alberi della foresta ci sia varietà, il modello risulterà essere molto stabile e robusto contro l'overfitting anche senza potatura degli alberi.
# 
# Oltre agli Iperparametri utilizzati ereditati dagli alberi decisionali, avremo iperparametri specifici che sono: dimensione della foresta; dimensione degli insiemi di addestramento di ogni albero; numero di features utilizzate. 
# 
# 
# ## Addestramento e iperparametri
# 
# Sia $C$ l'insieme di etichette che identificano le classi, $n$ il numero di esempi e $d$ il numero di caratteristiche. $X \in R^{n \times d}$ è la matrice che raccoglie il vettore delle caratteristiche per tutti gli esempi disponibili e $y \in C^n$ il vettore delle classi a cui appartengano gli esempi.
# 
# Sia $k$ il numero di alberi che compongono la foresta: per fare in modo che ci sia varietà tra gli alberi, ognuno di loro verrà addestrato su un sottoinsieme di dimensione $n'$ di esempi e un sottoinsieme di dimensione $d'$ di caratteristiche.
# 
# Tipicamente l'insieme degli esempi utilizzato per addestrare un singolo albero decisionale viene scelto operando $n$ estrazioni casuali con reinserimento tra gli $n$ esempi del dataset originale: questa tecnica è detta di *bootstrap*. Invece, le $d'$ caratteristiche vengono scelte attraverso estrazioni senza reinserimento; un valore tipico per $d'$ è $\sqrt{d}$.
# 
# Le scelte descritte garantiscono una buona variabilità sugli alberi, per convincerci di questo concentriamoci soltanto su alcune proprietà del bootstrap.
# 
# ### Bootstrap
# 
# Sia $I$ un sottoinsieme del dataset ottenuto con il bootstrap, calcoliamone la dimensione attesa per grandi valori di $n$.
# 
# Introduciamo $n$ variabili aleatorie $x_i$ così definite
# 
# $$
# x_i = \left\{
# \begin{array}{lcl}
# 1 & & \mbox{se l'esempio $i$ è in $I$}\\
# 0 & & \mbox{altrimenti}
# \end{array}
# \right.
# $$
# 
# Dalla precedente,
# 
# $$
# |I| = \sum_{i=1}^n x_i
# $$
# 
# quindi
# 
# $$
# E(|I|) = \sum_{i=1}^n E(x_i)
# $$
# 
# Il valore medio di $x_i$ equivale alla probabilità che $x_i$ sia $1$ che equivale a
# 
# $$
# 1 - Pr(\mbox{$i$ non venga mai scelto}) =
# 1-\left( 1 - \frac{1}{n}\right)^n
# $$
# 
# Al crescere di $n$, il secondo termine della differenza tende a $1/e$ da cui segue che
# 
# $$
# E(|I|) \rightarrow  n\left( 1-\frac{1}{e} \right) \approx 0.63 \cdot n.
# $$
# 
# Quindi circa il $37\%$ degli esempi resta fuori (*out of bag*). Questi possono essere messi da parte ed utilizzati per testare il modello.
# 
# Con il prossimo conto cerchiamo di capire quanto hanno in comune due sottoinsieme $I_0$ e $I_1$ ottenuti con la tecnica del bootstrap.
# 
# Calcoliamo $E(|I_0\cap I_1|)$. Analogamente a quanto fatto prima definiamo
# 
# $$
# x_i = \left\{
# \begin{array}{lcl}
# 1 & & \mbox{se l'esempio $i$ è in $I_0\cap I_1$}\\
# 0 & & \mbox{altrimenti}
# \end{array}
# \right.
# $$
# 
# quindi $E(|I_0 \cap I_1|) = \sum_{i=1}^n E(x_i)$. Questa volta
# 
# $$
# Pr(x_i = 1) = 1 - Pr(x_i=0)
# $$
# 
# $$
# = Pr(\mbox{$i$ non viene mai estratto per $I_0$ e non viene mai estratto per $I_1$})
# $$
# 
# $$
# = \left( 1-\left( 1 - \frac{1}{n}\right)^n \right)^2
# $$
# 
# $$
# \rightarrow \left( 1-\frac{1}{e} \right)^2 \approx 0.4
# $$
# 
# Quindi $E(|I_0 \cap I_1|) \approx 0.4\cdot n$. In altre parole, ogni coppia di alberi viene addestrata su insiemi che differiscono tra loro per circa il $66\%$ degli esempi. Questo, insieme alla scelta casuale delle feature contribuisce a creare alberi diversi tra di loro e questo favorisce il modello.

# ## Codice

# In[1]:


import os
import pandas as pd
import numpy as np

#from graphviz import Digraph


# ### Classe `DecisionTree`
# 
# La modifica da apportare alla classe `DecisionTree` riguarda l'introduzione della possibilità di addestrare l'albero su un sottoinsieme delle caratteristiche piuttosto che su tutte. Tra i parametri è stato aggiunto `num_feats` che permette di speficicare quante features utilizzare. Queste verranno scelte a caso nel metodo `__init__`. La funzione utilizzata sarà `choice` di `numpy.random` con la quale verranno selezionati casualmente gli indici delle feature; il parametro `replace = False` indica che l'estrazione avviene senza reinserimento.
# 
# L'altro metodo modicicato è `_get_best_split`, utilizzato durante l'addestramento per aggiungere nel modo migliore i nodi all'albero. Nel ciclo principale, anziché iterare su tutti gli indici delle caratteristice, itera su quelli selezionati in `__init__`.

# In[2]:


class DecisionTree(object):
    def __init__(self, max_depth=3, min_size=1, criterion='gini',
                 num_feats = None, random_state = 0):      
        impurity_funcs = {'gini': self._gini, 'entropy': self._entropy}
        
        self.max_depth = max_depth
        self.min_size = min_size
        self.tree = None
        
        self._impurity_fun = impurity_funcs[criterion]
            
        self._num_feats = num_feats
        self._random_state = random_state
        
        # indici delle features usate, in caso = None, tutte le features
        self._feature_indxs = None
            
    def fit(self, X, y):
        """ Costruisce l'albero di decisione """
        y = np.array(y).reshape(-1, 1)  # anziché vettore, una matrice ad una colonna x tutte le righe che servono
        
        '''
        dataset contiene sia X che y impilati verticalmente, questa è 
        la soluzione più conveniente per semplificare le operazioni
        di filtro delle righe che porterà alle suddivisioni del dataset che
        definiranno i nodi dell'albero
        '''
        
        if self._num_feats!= None and self._num_feats < X.shape[1]:
            rng = np.random.default_rng(seed=self._random_state)
            # indici delle features usate
            self._feature_indxs = rng.choice(np.arange(X.shape[1]), self._num_feats, replace=False)
        else:
            self._feature_indxs = np.arange(X.shape[1])
            
        
        dataset =  np.hstack((X, y)) # Concatenazione orizzontale
        self.tree = self._build_tree(dataset, 1)

    def _info_gain(self, dataset, groups):
        nl, nr = groups[0].shape[0], groups[1].shape[0]
        n = nl + nr
        ig = self._impurity_fun(dataset) - self._impurity_fun(groups[0])*nl/n - self._impurity_fun(groups[1])*nr/n
        return ig
        
    def _entropy(self, dataset):
        labs, occur = np.unique(dataset[:,-1], return_counts=True)
        score = 0
        for i, _ in enumerate(labs):
            proportion = occur[i] / dataset.shape[0]
            score += proportion * np.log2(proportion)
        return -score
    
    def _gini(self, dataset):
        labs, occur = np.unique(dataset[:,-1], return_counts=True)
        score = 0
        for i, _ in enumerate(labs):
            proportion = occur[i] / dataset.shape[0]
            score += proportion ** 2
        return 1-score


    def _split_dataset(self, index, value, dataset):
        """ Divide il dataset in due gruppi in base al confronto della caratteristica
        index con value"""
        mask = dataset[:, index] < value
        left, right = dataset[mask], dataset[~mask]

        return left, right

    def _get_best_split(self, dataset):
        """ Trova la feature (colonna di dataset) sulla quale esiste un valore tale che  
        Massimizza il guadagno informativo su tutte le possibili suddivisioni ottenibili usando
        tutte le possibili caratteristiche.

        Quindi per ogni caratteristica index e per ogni esempio row, si divide il dataset
        in base al test x[index] < row[index] e se ne calcola  il guadagno informativo.
        Si sceglie indx e row[index] in modo da massimizzare questo valore 
        """
        best_index, best_value, best_score, best_groups = None, None, float('-inf'), None
        for index in self._feature_indxs: 
            for row in dataset:
                groups = self._split_dataset(index, row[index], dataset)
                ig = self._info_gain(dataset, groups)
                if ig > best_score:
                    best_index, best_value, best_score, best_groups = index, row[index], ig, groups

        # ritorna un nudo
        return {'index': best_index, 'value': best_value, 'groups': best_groups}

    def _create_leaf(self, group):
        """ Crea un nodo foglia con la classe più comune """
        values, counts = np.unique(group[:,-1], return_counts=True)
        return values[np.argmax(counts)]

    def _split(self, node, depth):
        """ Cresce l'albero ricorsivamente """
        left, right = node['groups']
        #del node['groups']
        
        # Se uno dei gruppi ï¿½ vuoto, assegniamo una foglia
        if left.size == 0 or right.size == 0:
            node['left'] = node['right'] = self._create_leaf(np.vstack( (left, right) ))
            return

        # Fermiamo la crescita se abbiamo raggiunto la profonditï¿½ massima
        if depth >= self.max_depth:
            node['left'], node['right'] = self._create_leaf(left), self._create_leaf(right)
            return

        # Se il gruppo sinistro ï¿½ troppo piccolo, creiamo una foglia
        if len(left) <= self.min_size:
            node['left'] = self._create_leaf(left)
        else:
            node['left'] = self._get_best_split(left)
            self._split(node['left'], depth + 1)

        # Se il gruppo destro ï¿½ troppo piccolo, creiamo una foglia
        if len(right) <= self.min_size:
            node['right'] = self._create_leaf(right)
        else:
            node['right'] = self._get_best_split(right)
            self._split(node['right'], depth + 1)

    def _build_tree(self, dataset, depth):
        """ Costruisce l'albero a partire dai dati """
        root = self._get_best_split(dataset)
        self._split(root, depth)
        return root

    def _is_leaf(self, node):
        return not isinstance(node, dict)

    def _predict_example(self, node, row):
        """ Predice il valore di una singola riga """
        if row[node['index']] < node['value']:
            if self._is_leaf(node['left']):
                return node['left']
            else:
                return self._predict_example(node['left'], row)
                
        else:
            if self._is_leaf(node['right']):
                return node['right']
            else:
                return self._predict_example(node['right'], row)
            
    def predict(self, row):
        """ Predice la classe di una singola riga """
        return self._predict_example(self.tree, row)

    def predict_batch(self, X):
        """ Predice su un intero dataset """
        return [self.predict(row) for row in X]
    
    def draw_tree(self):
        self.the_tree = Digraph()
    
        def add_nodes_edges(node, parent_id=None, edge_lab = 'SI'):
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
    
            add_nodes_edges(node.get('left'), node_id, 'SI')
            add_nodes_edges(node.get('right'), node_id, 'NO')
    
        add_nodes_edges(self.tree)

    def show_tree(self):
        return self.the_tree


# ### Classe `RandomForest`
# 
# La seguente è una funzione di utilità, la moda, utilizzata per calcolare l'elemento più frequente tra quelli nella struttura in input. Oltre a ritornare l'elemento più frequente, ritorna anche il numero di volte in cui questo appare.

# In[3]:


def mode( a ):
    '''
    parametro: a, un array-like

    return: l'elemento più frequente ed il numero di occorrenze

    '''

    itms, cnts = np.unique(np.array(a), return_counts=True )

    return itms[np.argmax(cnts)], max(cnts)


# Il metodo `__init__` della classe `RandomForest` inizializza gli iperparametri che sono:
# 
# - `_n_trees`: il numero di alberi della foresta (valore di default 3)
# - `_max_samples`: il numero di esempi estratti dal dataset per formare l'insieme di addestramento di ogni singolo albero (valore di default il numero di righe del dataset)
# - `_max_feat_func`: il numero di features utilizzate per addestrare gli alberi è ottenuto usando questa funzione applicata al numero di features totali (valore di default la funzione radice quadrata)
# 
# Gli altri parametri servono per impostare gli iperparametri per il modello `DecisionTree`.
# 
# La selezione degli esempi è eseguita nel metodi `fit` usando ancora una volta la funzione `choice` di `numpy.random` ma questa volta il parametro `replace = True` per eseguire estrazioni con rimescolamento. Gli alberi vengono inseriti nella lista `trees`. Il metodo `fit` termina invocando il metodo `_oob_valutation` che esegue una valutazione del modello usando le istanze out-of-bag, ovvero quelle non estratte per l'addestramento. Più precisamente, durante l'addestramento, viene mantenuta aggiornata la struttura `_used_rows` che è un array di booleani di dimensione  `X.shape[0] ·_n_trees` con la proprietà  che   `_used_rows[i,t]` vale  `True` se e solo se l'esempio  `i` è stato utilizzato per addestrare l'albero  `t`. Il metodo `_oob_valutation` passa in rassegna tutti gli esempi e ognuno di questi viene valutato usando solo gli alberi per i quali non è stato utilizzato per l'addestramento. L'accuratezza ottenuta con questa procedura viene memorizzata nell'attributo `_oob_accuracy`.
# 
# La classificazione di una istanza `x` avviene attraverso il metodo `predict` che raccoglie le le classificazioni da ogni albero nell'array `predictions` per poi restituire il valore più frequente in quest'ultimo. 

# In[4]:


class RandomForest(object):
    def __init__(self, n_trees = 3, max_samples = None,
                 max_feat_func=np.sqrt, max_depth=3,
                 min_size=1, criterion='gini',
                 random_state = 0):
        
        self._n_trees = n_trees
        self._max_samples = max_samples
        self._max_feat_func = max_feat_func
        
        self._random_state = random_state
        
        self.max_depth = max_depth
        self.min_size = min_size        
        self._impurity_fun = criterion

        self.trees = []
        self._used_rows = None # struttura usata per valutazione oob
        
        
    def fit(self, X, y):
        # Numero di caratteristiche calcolate come funzione del
        # numero di colonne di X
        num_feats = int(self._max_feat_func(X.shape[1]))
        rng = np.random.default_rng(seed=self._random_state)

        self._used_rows = np.zeros( (X.shape[0], self._n_trees), dtype=bool)
        # used_rows[i,t] vale True se la riga i è stata usata per
        # addestrare l'albero t

        if self._max_samples == None:
            self._max_samples = X.shape[0]
             
        for i in range(self._n_trees):
            rnd_rows = np.unique(rng.choice(np.arange(X.shape[0]), self._max_samples, replace=True))
            self._used_rows[rnd_rows, i] = True # righe rnd_rows usate per albero i
            tree = DecisionTree(max_depth = self.max_depth, 
                                min_size = self.min_size,
                                criterion = self._impurity_fun,
                                num_feats = num_feats,
                                random_state = i
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
        '''
        ogni esempio verrà utilizzato per valutare le prestazioni degli alberi di cui era out-of-bag
        '''

        successes, n = 0, 0 # numero di successi e numero di esperimenti (esempi oob almeno una volta)
        
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

        self._oob_accuracy = successes/n

    def get_accuracy(self):
        return self._oob_accuracy
            





# ### Esempi
# 
# Testiamo il modello sull'intero dataset iris. 

# In[5]:

if __name__ == '__main__':
    s = os.path.join('dataset', 'iris.data')
    df = pd.read_csv(s,
                     header=None,
                     encoding='utf-8')
    
    
    X = df.iloc[:, [0, 1, 2, 3]].values
    y = df.iloc[:, 4].values
    
    
    # In[6]:
    
    
    rf = RandomForest(max_feat_func=lambda d: d-1, max_depth=3, n_trees = 5)
    rf.fit(X,y)
    
    preds = np.array([rf.predict(x)[0] for x in X]) == y
    
    print('Accuratezza su insieme di addestramento', preds.sum()/preds.shape[0])
    print('Accuratezza su esempi out-of-bag', rf.get_accuracy())
    

    # L'accuratezza sugli esempi out-of-bag è minore di quella sugli esempi di addestramento. Si tratta di overfitting? Per chiarire dividiamo il dataset iniziale in due parti: un insieme composto dall'80% degli esempi iniziali che verrà usato per l'addestramento; il restante 20% verrà usato soltanto per il test. La partizione è creata in modo casuale usando un array di booleani che verrà usato per filtrare le righe di `X` e gli elementi di `y`.
    
    # In[7]:
    
    
    n = X.shape[0]
    train_set_size = int(n*0.8)
    test_set_size = n - train_set_size
    
    np.random.seed(10)
    filter = np.array([True]*train_set_size+[False]*test_set_size)
    np.random.shuffle(filter)
    
    X_train, y_train = X[filter], y[filter]
    X_test, y_test = X[~filter], y[~filter]
    
    
    # In[8]:
    
    
    rf = RandomForest(max_feat_func=lambda d: d-1, max_depth=3, n_trees = 5)
    rf.fit(X_train,y_train)
    
    preds = np.array([rf.predict(x)[0] for x in X]) == y
    
    print('Accuratezza su insieme di addestramento', preds.sum()/preds.shape[0])
    print('Accuratezza su esempi out-of-bag', rf.get_accuracy())
    
    preds = np.array([rf.predict(x)[0] for x in X_test]) == y_test
    
    print('Accuratezza su insieme di test', preds.sum()/preds.shape[0])
    
    
    # L'accuratezza sugli esempi oob ancora risulta più bassa di quella dell'insieme di addestramento; invece quella sull'insieme di test è in linea. Questo ci dice che il motivo della minore accuratezza sugli oob potrebbe non essere dovuta all'overfitting ma al numero ridotto di alberi utilizzati nella valutazione oob.
    
    # # Esercizio
    # 
    # Testare il classificatore sul dataset [Wine](https://archive.ics.uci.edu/dataset/109/wine).
