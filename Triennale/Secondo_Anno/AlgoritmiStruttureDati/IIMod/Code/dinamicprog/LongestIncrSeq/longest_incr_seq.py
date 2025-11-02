def compute_opt(a: list[int]) -> tuple[list[int], int]:
    n = len(a)
    OPT = [0] * n
    for i in range(n):
        OPT[i] = 1
        m = 0
        k = 0
        for j in range(i):
            if a[j] < a[i] and m < OPT[j]:
                m = OPT[j]
        OPT[i] += m
    
    return OPT, max(OPT)

a = [4, 1, 8, 3, 4, 8, 2, 7, 5, 6, 9, 8]
opt, v = compute_opt(a)
print("Il vettore OPT è:", opt)
print("La lunghezza della sequenza più lunga è: ", v)

        