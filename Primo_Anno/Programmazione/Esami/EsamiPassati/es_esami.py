def printInt_Str_Float(l):
    l_int = []
    l_str = []
    l_float = []
    for elem in range(len(l)): # O(l)
        if type(l[elem]) == int:
            l_int.append(l[elem])   # l'append ha un costo costante
        if type(l[elem]) == str:
            l_str.append(l[elem])
        if type(l[elem]) == float:
            l_float.append(l[elem])
    
    k = len(l_int)
      
    if len(l_int) == len(l_str) == len(l_float) == k:
        for x in range(k): # O(k)
            print(l_float[x], l_int[x], l_str[x])
    else:
        print("k non valido!!\n")

def is_matrix(list_m):
    l = len(list_m)
    rad = abs(l ** 0.5)
    if(rad ** 2 == l and l > 0):
        return True
    return False

l = []
print(is_matrix(l))