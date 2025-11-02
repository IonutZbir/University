def merge1(a, b):
    """

    Args:
        a (iterable that can be ordered by <): ordered by <=
        b (iterable that can be ordered by <): ordered by <=
    
    Returns: una lista contenente gli elementi di l1 e l2 ordinati secondo la relazione <=
    """
    c = []
    i, j = 0, 0
    
    # sia n = len(a) + len(b)
    
    while i < len(a) and j < len(b): # eseguito <= n volte
        if a[i] < b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            j += 1

    # if i == len(a): # costo O(n)
    #     c.extend(b[j:])
    # else:
    #     c.extend[a[i:]]
    
    if i == len(a):
        t, k = b, j
    else:
        t, k = a, i
    while k < len(t):
        c.append(t[k])
        k += 1 
        
    return c








