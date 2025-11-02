def bubbleSort(a):
    n = len(a)
    for i in range(n - 1):
        j = 0
        while j < n - 1 - i:
            if a[j] > a[j + 1]:
                x = a[j]
                a[j] = a[j + 1]
                a[j + 1] = x
            j += 1
    return a


a = [3, 2, 5, 4, 1, 10, 20, 1, 40, 21, 4, 5]

print(bubbleSort(a))
