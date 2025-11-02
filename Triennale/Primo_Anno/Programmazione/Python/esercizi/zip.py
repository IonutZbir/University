a = [5, 3 ,8, 6, 14, 20]


def f(arr_input):
    counter = 0
    for x in range(2, len(arr_input)):
        if arr_input[x - 2] + arr_input[x - 1] == arr_input[x]:
            counter += 1
    return counter

def g(arr_input):
    counter = 0
    k,j = [],[]
    for x in range(len(arr_input) - 2):
        k = arr_input[x: x + 3]
        j.append(k)
    for i in zip(x for x in j):
        if i[0][2] == i[0][0] + i[0][1]:
             counter += 1
    return counter
print(g(a))