# Sia A[1:n] un vettore di n bit. Si progetti una struttura dati che prende in input il vettore A e sia in grado poi di rispondere a query 
# del tipo:
# - Differenza(i, j): resituisce la differenza in modulo fra il numero di uni e di zeri nel sottovettore A[i:j]

class Oracolo:

    class Coppia:
        def __init__(self, nZeri, nUni):
            self.nZeri = nZeri
            self.nUni = nUni

        def print_coppia(self):
            return (self.nZeri, self.nUni)

    def __init__(self, arr):
        self._oracolo = self._make_oracolo(arr)
        self._len = len(self._oracolo)

    def _make_oracolo(self, arr):
        n = len(arr)
        orac = [self.Coppia(0, 0)] * (n + 1)
        for i in range(n):
            if arr[i] == 0:
                nZeri = orac[i].nZeri + 1
                nUni = orac[i].nUni
            else:
                nZeri = orac[i].nZeri
                nUni = orac[i].nUni + 1

            orac[i + 1] = self.Coppia(nZeri, nUni)

        return orac

    def query(self, i, j):
        i += 1
        j += 1
        nZeri = self._oracolo[j].nZeri - self._oracolo[i - 1].nZeri
        nUni = self._oracolo[j].nUni - self._oracolo[i - 1].nUni
        return nZeri - nUni if nZeri > nUni else nUni - nZeri

    def print_oracolo(self):
        print("[ ", end="")
        for i in range(1, self._len - 1):
            print(self._oracolo[i].print_coppia(), ", ", end="")
        print(self._oracolo[self._len - 1].print_coppia(), " ]")

a = [0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1]
i = 4
j = 6
oracolo = Oracolo(a)
res = oracolo.query(i, j)
oracolo.print_oracolo()
print(a)
print(res)
print(i, j)
