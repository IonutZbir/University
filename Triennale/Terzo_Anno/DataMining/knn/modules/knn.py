#!/usr/bin/env python
# coding: utf-8

# # k-Nearest Neighbors (KNN)

# In[1]:


import os
import pandas as pd
import numpy as np


# In[2]:


def argselection(a, x, k = None, key = None):
    '''
    input: a, una sequenza; x un oggetto, k un intero; key una funzione dei valori di a e x
    
    restituisce un array con i primi k elementi di a in ordine di grandezza rispetto
    alla funzione key

    se k non indicato, viene usata per k la dimensione dell'array

    se key non indicato, viene usata la funzione identità 
    '''
    if k == None:
        k = len(a)
    if key == None:
        key = lambda y, _: y
    arg_sel_array = []
    for i in range(k):
        m = None
        for j in range(len(a)):
            if m == None or key(a[j], x) < key(a[m], x):
                if j not in arg_sel_array:
                    m = j
        arg_sel_array.append(m)
            
    return np.array(arg_sel_array)
        
def mode( a ):
    '''
    parametro: a, un array-like

    return: l'elemento più frequente ed il numero di occorrenze
    '''

    itms, cnts = np.unique(np.array(a), return_counts=True )

    return itms[np.argmax(cnts)], max(cnts)

def euclidean_dist(a0, a1):
    return np.linalg.norm(a0 - a1)

class KNN(object):
    def __init__(self, k = 5, distance = None):
        self.k = k
        if distance == None:
            self._dist = euclidean_dist
        else:
            self._dist = distance
    
    def fit(self, X, y):
        self.X = X
        self.y = y
        
    def predict(self, x):        
        # Ottiene gli indici dei k punti più vicini
        k_indices = argselection(self.X, x, k=5, key = self._dist)
        
        # Prende le etichette corrispondenti
        return mode(self.y[k_indices])
    


# In[3]:

if __name__ == '__main__':

    s = os.path.join('dataset', 'iris.data')
    df = pd.read_csv(s,
                     header=None,
                     encoding='utf-8')
    
    
    X = df.iloc[:, [0, 1, 2, 3]].values
    y = df.iloc[:, 4].values
    
    X_std = (X-X.mean(0))/X.std(0)
    
    
    # In[4]:
    
    
    n = X_std.shape[0]
    train_set_size = int(n*0.8)
    test_set_size = n - train_set_size
    
    np.random.seed(10)
    filter = np.array([True]*train_set_size+[False]*test_set_size)
    np.random.shuffle(filter)
    
    X_train, y_train = X_std[filter], y[filter]
    X_test, y_test = X_std[~filter], y[~filter]
    
    
    # In[5]:
    
    
    knn = KNN()
    knn.fit(X_train, y_train)
    
    preds = np.array([knn.predict(x)[0] for x in X_test]) == y_test
    print('Accuratezza ', preds.sum()/preds.shape[0])
    
