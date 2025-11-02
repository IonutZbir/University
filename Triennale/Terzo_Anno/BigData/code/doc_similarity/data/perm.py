import random

def create_perm(n: int) -> list:
    p = []
    for _ in range(n):
        k = random.randint(0, n - 1)
        while k in p:
            k = random.randint(0, n - 1)
        p.append(k)    
        
    return p

def get_perm(x: list, p=None) -> list:
    n = len(x)
    if p == None: 
        p = create_perm(n)
    print("permutation: ", p)
    out = [0] * n
    for i in range(n):
        out[i] = x[p.index(i)]
    return out

x = [1, 1, 0, 0, 0, 1, 1]
p = [1, 2, 6, 5, 0, 4, 3]
p_x = get_perm(x, p)
print("x before permutation: ", x)
print("x after permutation: ", p_x)
