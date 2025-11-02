# Sia A[1:n] un vettore di n interi positivi. Diremo che un elemente A[i] è felice al quadrato se esiste un indice 
# j tale che A[j] = A[i]^2
# Si progetti un algoritmo che dato A indica in tempo O(n log n) se esiste almeno un elemento felice al quadrato. 

def integer_sort(arr):
    m = max(arr)
    b = [0] * (m + 1)
    for i in range(len(arr)):
        b[arr[i]] += 1

    j = 0
    for i in range(m):
        while b[i] > 0:
            arr[j] = i
            j += 1
            b[i] -= 1
    return arr

def binary_search(arr, start, end, val):
    if end < start:
        return -1
    m = (start + end) // 2
    if arr[m] == val:
        return m
    elif arr[m] > val:
        return binary_search(arr, start, m - 1, val)
    else:
        return binary_search(arr, m + 1, end, val)

def oracolo(arr):
    print(a)
    oracolo = integer_sort(arr)
    print(oracolo)
    for i in range(len(oracolo)):
        k = oracolo[i]**2
        j = binary_search(oracolo, 0, len(oracolo), k)
        if(j != -1):
            return j
    return -1

a = [2, 5, 100, 7, 10, 9, 21]
print(oracolo(a))




