def insertion(array):
    for i in range(1, len(array)):
        while i > 0:
            a = array[i]
            b = array[i - 1]
            if a < b:
                x = a
                array[i] = b
                array[i - 1] = x
                i -= 1
    return array

a = [10, 4, 1, 32, 450, 2, 20, 10, 0, 75]
#a = [3, 4, 2, 5, 1]
print(insertion(a))
