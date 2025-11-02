def cioccolata(G, L):
    L += 1
    OPT = [0] * L

    for j in range(1, L):
        max_value = 0
        for k in range(j):
            current_value = G[j - k] + OPT[k]
            if current_value > max_value:
                max_value = current_value
        OPT[j] = max_value
    return OPT[L - 1], OPT


G = [0, 6, 10, 20, 21, 25]
sol, OPT = cioccolata(G, 5)
print(sol, OPT)
