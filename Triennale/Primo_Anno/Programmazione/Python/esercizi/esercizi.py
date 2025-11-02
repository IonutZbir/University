def intersection_list(l1, l2):
    # intersezione dei elementi di 2 liste: costo O(min(len_l1, len_l2))
    inter = []
    d_max = {}
    if(len(l1) <= len(l2)):
        for x in l2:
            d_max[x] = d_max.get(x, 1)
        for key in l1:
            if d_max.get(key) != None:
                inter.append(key)
    else:
        for x in l1:
            d_max[x] = d_max.get(x, 1)
        for key in l2:
            if d_max.get(key) != None:
                inter.append(key)
    return inter

def intersection_dict_key(d1, d2):
    # intersezione delle chiavi di due dizionari: costo O(min(len_d1, len_d2))
    inter = []
    if(len(d1) <= len(d2)):
        for key in d1:
            if(d2.get(key) != None):
                inter.append(key)
    else:
        for key in d2:
            if(d1.get(key) != None):
                inter.append(key)
    return inter

def union_dict_key(d1, d2):
    # unione delle chiavi di due dizionari: costo O(n), dove n è la lunghezza del dizionario unione
    if(len(d1) <= len(d2)):
        for key in d1:
            if d2.get(key) == None:
                d2[key] = d1[key]
        return list(d2.keys())
    else:
        for key in d2:
            if d1.get(key) == None:
                d1[key] = d2[key]
        return list(d1.keys())

def intersection_key_value(d1, d2):
    # intersezione delle chiavi e dei valori di due dizionari: costo O(min(len_d1, len_d2))
    inter = {}
    if(len(d1) <= len(d2)):
        for key in d1:
            if(d2.get(key) != None):
                inter[key] = inter.get(key, [])
                if inter[key] != []:
                    inter[key].append(d2.get(key))
                    inter[key].append(d1.get(key))
                else:
                    inter[key] = [d2.get(key), d1.get(key)]
    else:
        for key in d2:
            if(d1.get(key) != None):
                inter[key] = inter.get(key, [])
                if inter[key] != []:
                    inter[key].append(d1.get(key))
                    inter[key].append(d2.get(key))
                else:
                    inter[key] = [d1.get(key), d2.get(key)]
    return inter
        
def union_key_value(d1, d2):
    # unione delle chiavi e dei valori di due dizionari: costo O(min(len_d1, len_d2))
    
    d_min = d2 if len(d1) > len(d2) else d1
    d_max = d1 if len(d1) > len(d2) else d2

    for key in d_min:
        d_max[key] = d_max.get(key, [])
        if d_max[key] != []:
            d_max[key] = [d_max[key]]
        d_max[key].append(d_min[key])
    
    return d_max

d1 = {
    'chiave1': 1,
    'chiave2': 2,
    'chiave3': 3,
    'chiaveC': 300
}

d2 = {
    'chiaveA': 100,
    'chiave3': 200,
    'chiaveC': 100,
    'chiave2': 12321
}

print(intersection_key_value(d1, d2))


def occurences(l):
    d = {}
    for x in l:
        d[x] = d.get(x, 0) + 1
    return d

def get_min( d ):
    """
        d è un dict che mappa lettere su int
        restituisce il valore in d associato alla prima chiave
        in ordine alfabetico. Per esempio, se
        d = {'x': 11, 'b':12}, get_min(d) ritorna 12.
    """
    l = sorted(d.keys(), key = lambda x: x)
    return l[0]

def move_max( a ):
    '''
            Precondizione: a è una lista di numeri
            Sposta il massimo di a in fondo alla lista,
            gli altri elementi occuperanno le posizioni precedenti
    '''
    m = max(a)
    a.remove(m)
    a.append(m)
        

def sort_by_len(l):
    l = sorted(l, key = lambda x: len(str(x)) - 1 if type(x) == float else len(str(x)))
    return l    

def sort_by_occurrences(s):
    d = {}
    for x in s:
        d[x] = d.get(x, 0) + 1
    
    return ''.join(sorted(d.keys(), key = lambda x: d[x]))

def inverti_dizionario(d):
    d_inv = {}
    for k, v in d.items():
        if v in d_inv:
            d_inv[v].append(k)
        else:
            d_inv[v] = [k]

    return d_inv    


def show_board( board ):
    n = len(board)
    m = n*[n*[0]]
    for i in range(n):
        for j in range(n):
            if i == board[j]:
                m[j] = (n-1-i) * '_' + '#' + (i) * '_'
    for r in range(len(m)):
        for c in range(len(m[r])):
            print(m[c][r], end='')
        print()
        
def trova_anagrammi(parole):
    anagrammi = {}
    for parola in parole:
        chiave = "".join(sorted(parola))
        if chiave in anagrammi:
            anagrammi[chiave].append(parola)
        else:
            anagrammi[chiave] = [parola]
    return anagrammi
        
def dict_anagrammi(parole):
    #Scrivi una funzione che prende in input una lista di parole e
    # restituisce un dizionario in cui le chiavi sono le parole ordinate alfabeticamente e
    # i valori sono le liste di parole originali che sono anagrammi tra loro.
    anagrammi = trova_anagrammi(parole)
    a2 = {}
    for parola in parole:
        chiave = "".join(sorted(parola))
        if chiave in anagrammi:
            a2[parola] = anagrammi[chiave]
    a2 = dict(sorted(a2.items(), key=lambda x: x[0]))
    return a2
    
class calendar:
    # Scrivi un programma che gestisca un calendario degli eventi.
    # Utilizza un dizionario in cui le chiavi sono le date in formato "giorno/mese/anno" e
    # i valori sono le liste degli eventi previsti per quella data. Implementa funzioni per aggiungere un evento,
    # rimuovere un evento e visualizzare gli eventi di una data specifica.
    def __init__(self):
        self.calendar = {}
    
    def add_event(self, date, event):
        # date: dd/mm/aaaa
        # event: any string
        self.calendar[date] = self.calendar.get(date, [])
        self.calendar[date].append(event)

    def remove_event(self, date, event):
        # date: dd/mm/aaaa
        # event: any string
        self.calendar[date] = self.calendar.get(date, [])
        if self.calendar[date] != []:
            self.calendar[date].remove(event)
    
    def show_events(self, date):
        self.calendar[date] = self.calendar.get(date, [])
        if self.calendar[date] != []:
            print("Events in date:", date)
            for i in range(len(self.calendar[date])):
                print(f"{i + 1}:  {self.calendar[date][i]}.")
  
class chess:
    # Scrivi un programma che simuli una scacchiera utilizzando un dizionario.
    # Le chiavi del dizionario rappresentano le coordinate degli scacchi, ad esempio "A1", "E5", e
    # i valori sono i pezzi degli scacchi presenti in quella posizione.
    # Implementa funzioni per muovere i pezzi sulla scacchiera, controllare se una mossa è valida e
    # verificare se un pezzo può "mangiare" un altro pezzo.
    def __init__(self):
        self.board = {  "A1": (2, 7), "B1": (3, 7), "C1": (4, 7), "D1": (5, 7), "E1": (6, 7), "F1": (4, 7), "G1": (3, 7), "H1": (2, 7),
                        "A2": (1, 7), "B2": (1, 7), "C2": (1, 7), "D2": (1, 7), "E2": (1, 7), "F2": (1, 7), "G2": (1, 7), "H2": (1, 7),
                        "A3": (0, 0), "B3": (0, 0), "C3": (0, 0), "D3": (0, 0), "E3": (0, 0), "F3": (0, 0), "G3": (0, 0), "H3": (0, 0),    
                        "A5": (0, 0), "B5": (0, 0), "C5": (0, 0), "D5": (0, 0), "E5": (0, 0), "F5": (0, 0), "G5": (0, 0), "H5": (0, 0),
                        "A6": (0, 0), "B6": (0, 0), "C6": (0, 0), "D6": (0, 0), "E6": (0, 0), "F6": (0, 0), "G6": (0, 0), "H6": (0, 0),
                        "A7": (1, 8), "B7": (1, 8), "C7": (1, 8), "D7": (1, 8), "E7": (1, 8), "F7": (1, 8), "G7": (1, 8), "H7": (1, 8),
                        "A8": (2, 8), "B8": (3, 8), "C8": (4, 8), "D8": (5, 8), "E8": (6, 8), "F8": (4, 8), "G8": (3, 8), "H8": (2, 8) }
        self.__pieces = {1: "Pedone", 2: "Torre", 3: "Cavallo", 4: "Alfiere", 5: "Regina", 6: "Re", 7: "Black", 8: "White"}
        self.__MAX = 8
        
        
    def __check_pos(self, pos_i, pos_f, piece):
        col_i, row_i = pos_i[0], int(pos_i[1])
        col_f, row_f = pos_f[0], int(pos_f[1])
        if(piece == 1):
            if(row_f > row_i):
                c = row_f - row_i == 2 or row_f - row_i == 1 if row_i == 7 or row_i == 2 else row_f - row_i == 1
            else:
                c = row_i - row_f == 2 or row_i - row_f == 1 if row_i == 7 or row_i == 2 else row_f - row_i == 1
            return (c) and (col_i == col_f) and (self.board[pos_f] == 0) and row_f <= self.__MAX      
        # elif(piece == 2):
        # elif(piece == 3):
        # elif(piece == 4):
        # elif(piece == 5):
        # elif(piece == 6):    
        
    def white_move(self, pos_i, pos_f, piece):
        print(self.__check_pos(pos_i, pos_f, piece))
        if self.__check_pos(pos_i, pos_f, piece):
            print(f"Sposto il {self.__pieces[piece]} in posizione {pos_f}")
    
    def black_move(self, pos_i, pos_f, piece):
        print(self.__check_pos(pos_i, pos_f, piece))
        if self.__check_pos(pos_i, pos_f, piece):
            print(f"Sposto il {self.__pieces[piece]} in posizione {pos_f}")

