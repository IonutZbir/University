def BubbleSort(lista, inplace=True, key = lambda x: x):
    
    if inplace:
        newL = lista
    else:
        newL = lista[:]
    
    n = len(newL)
    ordinata = False
    j = 0
    count = 0
    while not ordinata:
        ordinata = True
        i = 0
        while i < n - 1 - j:
            current_el = key(newL[i])
            next_el = key(newL[i + 1])
            if current_el > next_el:
                # se la lista è ordinata non entro
                newL[i], newL[i + 1] = newL[i + 1], newL[i]                
                ordinata = False
            count += 1
            i += 1
        j += 1
    return newL, count
# costo computazione n^2



# Ordinare L in modo che i numeri precedano le strighe, 
# i numeri siano ordinati dal piu piccolo al piu grande,
# le stringhe in modo lessicografico


def num_str( v ):
    if type(v) in (float, int):
        return (0, v)
    else: 
        return (1, len(v))
    
    
a = [5, 7 ,2, 1, 9, 0]
k = 1
z = 0
for y in range(len(a) - z):
    for x in range(len(a) - k):
        if a[x] >= a[x + 1]:
            m = a[x + 1]
            a[x + 1], a[x] = a[x], m
        elif x == len(a) - k + 1:
            k += 1
    z += 1
print(a)