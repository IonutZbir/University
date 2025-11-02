def borsa(a):
    diff = a[1] - a[0]
    i, j, I, J, min = 1, 2, 0, 1, 0 
    while j < len(a):
        if a[i] <= a[min]:
            min = i
        if a[j] - a[min] > diff: # and min < j:
            diff = a[j] - a[min]
            J = j
            I = min
        i += 1
        j += 1
    return I, J, diff

a = [20, 20, 15, 40, 5, 2]
print(borsa(a))

