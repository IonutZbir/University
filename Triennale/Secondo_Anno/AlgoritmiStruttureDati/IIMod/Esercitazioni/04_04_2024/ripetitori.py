def calcolo_istallazione(low, high):
    n = len(low)
    OPT = [0] * (n + 3)
    for i in range(n - 1, -1, -1):
        OPT[i] = min([low[i] + OPT[i + 1], low[i] + OPT[i + 2], high[i] + OPT[i + 3]])
    print(OPT)
    return OPT[0]


low = [2, 1, 3, 4, 4, 7, 1]
high = [5, 8, 3, 5, 4, 8, 5]

k = calcolo_istallazione(low, high)
print(k)
