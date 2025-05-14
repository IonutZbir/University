import random


def maxCharCount(str1, str2):
    max = 0
    char = ""
    for i in range(len(str1)):
        count = 0
        for z in range(len(str2)):
            if str1[i] == str2[z]:
                count += 1
        if count > max:
            max = count
            char = str1[i]
    return char


def mcd(a, b):
    if not (a >= b):
        return None
    r = a % b
    while r > 0:
        q = b // r
        if b % q == 0:
            return r
        r = b % q
        b = q
    return b


def replaceVocali(str):
    vocali = "aeiouAeiou"
    new = ""
    for i in str:
        if i in vocali:
            new += "*"  # new += ' '
        else:
            new += i
    return new


def findString(stringa, strToFind):
    contenuto = False
    c1 = 0
    if len(stringa) >= len(strToFind):
        while c1 <= len(stringa) - len(strToFind) and not contenuto:
            c2 = 0
            while c2 < len(strToFind) and strToFind[c2] == stringa[c2 + c1]:
                c2 += 1
            if c2 == len(strToFind):
                contenuto = True
            else:
                c1 += 1
    if contenuto:
        return c1
    else:
        return False


def nDecimals(n=3):
    r = f"{random.random() + 1 * random.random() * 100:.{n}f}"
    return r


def nDecimalsV2(n=3):
    r = "0."
    for i in range(n - 1):
        r += str(random.randint(0, 9))
    r += str(random.randint(1, 9))
    return float(r)


def print_v(*strings):
    i = 0
    terminato = False
    while not terminato:
        terminato = True
        row = ""
        for str in strings:
            if len(str) > i:
                row += str[i]
                terminato = False
            else:
                row += " "
        i += 1
        print(row)


def prova(*strings):
    maxLen = 0
    for str in strings:
        if len(str) > maxLen:
            maxLen = len(str)
    for i in range(maxLen):
        row = ""
        for j in strings:
            if len(j) > i:
                row += j[i]
            else:
                row += " "
        print(row)


def hist(h0, h1, *numbers):
    """Dati 3 segmenti adiacenti ed n float si vuole calcolare quanti degli n float ricadono in ogni segmento.
    I segmenti sono rappresentati da 2 float h0 e h1 che definiscono i segmenti: (-∞, h0), [h0, h1), [h1, ∞].
    Si progetti una funzione che prenda in input la descrizione di 3 segmenti (h0 e h1) e un numero variabile di float e
    restituisca una terna di interi che rappresenta il numero di float che ricade in ciascuno dei 3 segmenti.

    Args:
        h0 (integer)
        h1 (integer)
        numbers (float)
    Return:
        tuple
    """
    e1, e2, e3 = (
        0,
        0,
        0,
    )  # contatori che contano quanti elementi sono presenti in ciascun segmento
    for n in numbers:
        if n < h0:
            e1 += 1
        if h0 <= n < h1:
            e2 += 1
        if n >= h1:
            e3 += 1
    return e1, e2, e3


# Esercizio lezione 9 del 07/11/2022


def init_tuple(n, v=lambda a: 0):
    t = ()
    for i in range(n):
        t += (v(i),)
    return t


def i_pos(i):
    return i


def i_dis(i):
    return i * 2 + 1


def i_str(i, char="*"):
    i += 1
    return char * i


def i_tuple(i):
    return (i,) * 10


def print_tuple(t):
    for i in range(len(t)):
        print(t[i])


def remNone(l):
    """
    Si progetti una funzione, denominata rem_none,
    che prenda in input una lista ed elimini da questa tutti gli elementi a valore None

    Args:
        l (list): list of random elements
    """
    i = 0
    while i < len(l):
        if l[i] == None:
            del l[i]
        else:
            i += 1
        # print(len(l) , i)


def init_list(n, v=lambda a: None):
    l = []
    for i in range(n):
        l.append(v(i))
    return l


def hist(numbers, bins):
    """
    Input:  numbers una lista di m float
            bins una lista di n-1 floats ordinati in modo crescente
    Output: una lista h di n floats tale che:
        - h[0] = numero di elementi in a < bins[0]
        - h[n-1] = numero di elementi in a >= bins[n-2]
        - per i = 1,..., n-2, h[i] = numero di elementi in a >= bins[i-1] e < bin[i]
    """

    out = [0] * (len(bins) + 1)

    for n in numbers:
        if n < bins[0]:
            out[0] += 1
        if n >= bins[-1]:
            out[-1] += 1
        for i in range(1, len(bins)):
            if bins[i - 1] <= n < bins[i]:
                out[i] += 1
    return out


def f(n):
    c = 0
    for i in range(1, n + 1):
        for j in range(1, n - i + 1):
            c += 1
    return c


n = 6
print(f(n))
