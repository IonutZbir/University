# Sia A[1:n] un vettore di n bit. Si progetti un oracolo che puo essere costruito in tempo O(n) e che sia in grado di rispondere in tempo costante a:
# - q(i): dai i, restituire il piu piccolo indice j >= i tale che A[i] = 1. Se tale indice j non esiste allora la risposta alla domanda è -1
class Oracolo:
    def __init__(self, arr):
        self._oracolo = self._make_oracolo(arr)

    def _make_oracolo(self, arr):
        # Idea: creare un vettore orac tale che orac[k] = primo j >= i tale che arr[j] = 1
        n = len(arr)
        orac = [0] * n
        if arr[n - 1] == 0:
            orac[n - 1] = -1
        else:
            orac[n - 1] = n - 1
        for k in range(n - 2, -1, -1):
            if arr[k] == 1:
                orac[k] = k
            else:
                orac[k] = orac[k + 1]
        return orac

    def query_oracolo(self, i):
        return self._oracolo[i]
    
    def print_oracolo(self):
        print(self._oracolo)

a = [1, 0, 1, 1, 0, 1, 0, 0, 0, 1]
#a = [1, 1, 1, 1]
orac = Oracolo(a)
res = orac.query_oracolo(1)
print(res)
orac.print_oracolo()


