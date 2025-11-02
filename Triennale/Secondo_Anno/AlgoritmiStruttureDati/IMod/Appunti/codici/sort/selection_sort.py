def selection_sort(arr: list) -> list:
    for i in range(len(arr) - 1):
        min = i # indice nell'array in cui si trova il minimo
        for j in range(i + 1, len(a)):
            if(arr[j] < arr[min]):
                min = j # aggiorno il minimo
        arr[min], arr[i] = arr[i], arr[min] # scambio, portando il minimo all'inizio dell'array
    return arr

a = [7, 2, 4, 5, 3, 1, 20, 0]
print(selection_sort(a)) 
