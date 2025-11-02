class House:
    def __init__(self, red, green, blue) -> None:
        self.red = red
        self.green = green
        self.blue = blue


def create_houses():
    return [
        House((7, "R"), (3, "G"), (16, "B")),
        House((6, "R"), (8, "G"), (10, "B")),
        House((7, "R"), (9, "G"), (4, "B")),
        House((8, "R"), (22, "G"), (2, "B")),
        House((9, "R"), (12, "G"), (5, "B")),
        House((20, "R"), (8, "G"), (7, "B")),
    ]


def house_coloring(Houses):
    n = len(Houses)
    OPT = [(0, 0)] * n

    R = [house.red for house in Houses]
    G = [house.green for house in Houses]
    B = [house.blue for house in Houses]

    print("[INFO]: RED ", R)
    print("[INFO]: GREEN", G)
    print("[INFO]: BLUE", B)

    OPT[0] = min(R[0], G[0], B[0])

    i = 1
    for elem in OPT:
        new_elem = [0, 0]
        cost, color = elem

        if i == n:
            break

        if color == "R":
            new_elem = list(min(G[i], B[i]))
        elif color == "G":
            new_elem = list(min(R[i], B[i]))
        elif color == "B":
            new_elem = list(min(G[i], R[i]))

        new_elem[0] += cost

        OPT[i] = tuple(new_elem)
        i += 1

    return OPT, OPT[n - 1][0]


houses = create_houses()
OPT, sol = house_coloring(houses)
print("[INFO]: Il costo della soluzione ottima è", sol)
print("[INFO]: La soluzione ottima è", OPT)
