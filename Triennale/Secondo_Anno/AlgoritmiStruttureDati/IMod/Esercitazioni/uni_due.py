def bin_search(arr, n, start, end):
    if start > end:
        return -1
    m = (start + end) // 2
    if arr[m] == n:
        return m
    if arr[m] < n:
        return bin_search(arr, n, m + 1, end)
    else:
        return bin_search(arr, n, start, m - 1)

def sum_uno_due(arr, h):
    n = len(arr)
    ones = bin_search(arr, 2, 0, n)
    
    print(ones)

    if ones < 0:
        return -1
    
    if ones == h:
        return ones

    if (ones % 2 == 0 and h % 2 == 0) or (ones % 2 == 1 and h % 2 == 1):
        diff = h - ones
        twos = diff / 2
        print(f"Ones: {ones} - Twos: {twos}")
        return ones + twos
    return -1

k = [1, 4, 6, 10, 11, 40]
a = [1, 1, 1, 1, 2, 2]
print(bin_search(a, 2, 0, len(a)))
