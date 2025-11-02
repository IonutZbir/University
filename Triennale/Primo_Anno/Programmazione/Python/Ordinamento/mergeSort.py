#num_comparisons = 0

def merge(a, lx, cx, rx):
    num_comparisons = 0
    """
    _summary_

    Parameters
    ----------
    a : lista di valori confrontabili con <
        con a[lx:cx] e a[cx:rx] ordinati
    lx , cx, rx : int
        indici, lx < cx < rx

    Returns
    -------
    None
    
    Output
    -------
    muta a in modo tale che a[lx:rx] sia ordinata
    """
    c = []
    i, j = lx, cx
    
    # sia n = len(a)
    # sia m = rx - lx
                                                    
    while i < cx and j < rx: # eseguito <= m volte     
        num_comparisons += 1
        if a[i] < a[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(a[j])
            j += 1
    # estendo c con gli elementi rimanenti in una delle 2 liste a[lx:cx], a[cx:rx]
    if i == cx:             
        k, last_index = j, rx
    else:
        k, last_index = i, cx
    while k < last_index: # O(m) m = rx-lx
        c.append(a[k])
        k += 1
    
    #a = a[:lx] + c + a[rx:] # O(n), non va bene!!!
    for i in range(rx - lx): # O(m)
        a[lx + i] = c[i]
    
    return num_comparisons

    
            
def mergeSort(a, lx = 0, rx = None): 
    """
    _summary_

    Parameters
    ----------
    iter : lista 
        lista di elementi per cui vale la relazione di <
    lx : int
        indici in a
    rx : int
        indici in a
    lx < rx

    Returns
    -------
    None
    
    Output
    -------
    Muta a in modo tale a[lx:rx] sia ordinata con <
    """
    
    if rx == None:
        rx = len(a)
        
    if lx == rx or rx == lx + 1:
        return 0
    cx = (rx + lx) // 2
    nL = mergeSort(a, lx, cx)
    nR = mergeSort(a, cx, rx)
    n = merge(a, lx, cx, rx)
    return n + nL + nR


a = [78, 63, 41, 35, 24, 20, 12, 9, 5, 3, 2]
mergeSort(a)
# print(num_comparisons)
# print(a)