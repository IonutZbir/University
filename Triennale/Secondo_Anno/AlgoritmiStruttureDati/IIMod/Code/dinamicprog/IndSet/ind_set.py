def compute_soltion(values: list) -> list:
    n = len(values)
    OPT = [0] * n

    OPT[0] = values[0]
    OPT[1] = max(values[0], values[1])

    for i in range(1, n):
        OPT[i] = max(OPT[i - 1], values[i] + OPT[i - 2])

    return OPT


def find_solution(OPT, values: list) -> list:
    SOL = []
    j = len(OPT) - 1

    while j > 1:
        if OPT[j - 1] >= values[j] + OPT[j - 2]:
            j -= 1
        else:
            SOL.append(values[j])
            j -= 2

    if (j == 1) and (values[1] > values[0]):
        SOL.append(values[1])
    else:
        SOL.append(values[0])

    return SOL


def indipendent_set(values: list) -> tuple[int, list]:
    OPT = compute_soltion(values)
    SOL = find_solution(OPT, values)
    return OPT[-1], SOL


OPT, SOL = indipendent_set([1, 4, 8, 4, 3, 10])
print("[INFO]: Il valore della soluzione ottima è: ", OPT)
print("[INFO]: La soluzione ottima è: ", SOL)
