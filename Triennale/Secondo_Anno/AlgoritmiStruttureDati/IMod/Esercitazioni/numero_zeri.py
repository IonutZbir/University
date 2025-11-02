def n_zeri(arr):
    u = 0
    n = len(arr)
    for i in range(n):
        u += arr[i]

    z = n - u
    z_i = 0

    for i in range(n):
        if arr[i] == 0:
            z_i += 1

        # calcolo il numero di uni dall'indice i in poi    
        u = (n - i) - (z - z_i)
        
        print(f"Z: {z}, U: {u}, ZI:{z_i}, I:{i}")

        if z_i == u:
            return i - 1 
    return -1

a = [0, 1, 1, 1, 1, 1, 1]
a = [0, 0, 0, 0, 0, 0, 1]
a = [0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1]
print(n_zeri(a))
