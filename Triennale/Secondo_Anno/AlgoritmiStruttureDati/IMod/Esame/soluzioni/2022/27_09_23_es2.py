# Sia A[1:n] un array di n bit. Si progetti una struttura dati che prende in input il vettore A e sia in grado poi 
# di rispondere a query del seguente tipo:
# BlockSize(i): dato un indice i, restituisce la lunghezza del più grande blocco di zero contigui che contiene l'indice 
# i. Se A[i] = 1, allora la risposta alla query è 0

class Oracolo:
    def __init__(self, arr):
        self._oracolo = self._make_oracolo(arr)

    def _make_oracolo(self, arr):
        n = len(arr)
        b = [0] * n
        c = 0
        for i in range(n):
            if arr[i] == 0:
                c += 1
                b[i] = c
            elif arr[i] == 1:
                c = 0
                b[i] = c

        for i in range(n - 2, -1, -1):
            if arr[i] == 1:
                b[i] = 0
            elif arr[i] == 0 and arr[i + 1] == 1:
                continue
            else:
                b[i] = b[i + 1]
        
        return b
    
    def query(self, i):
        return self._oracolo[i]

    def print_oracolo(self):
        print(self._oracolo)

a = [0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0]
orac = Oracolo(a)
print(a)
orac.print_oracolo()
print(orac.query(5))
