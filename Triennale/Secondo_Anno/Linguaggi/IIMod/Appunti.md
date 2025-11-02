Scrivere un programma prolog significa sceivere un insieme di predicati.
- Fatti
- Regole


X è fratello di Y se (:-) [Z genitore di X e (,) Z genitore di Y] 

=> fratello(X, Y) :- [genitore(Z, X), genitore(Z, Y)] è un regola

=> genitore(mario, dario), genitore(mario, gino) sono fatti 

X (maiuscolo) - variabile di cui vogliamo sapere il valore
_x - variabile di cui non vogliamo sapere il valore
_ - variabile che non viene unificata

a....(minuscolo) - costanti
1.... - numeri

fratello(dario, gino) ? vero o falso
-> assovio dario a X e gino a Y

unificare: valore associato alla variabile, e sara associato a tutti i nomi in quel istante

funzione -> predicato
funzionare -> predicare
ricorsione -> indunzione
assegnamento -> unificare

## Liste 

Induzione strutturale

Lista: [a, b, c, d, e]

[H | T] -> modalità di scrivere la lista testa|coda

H: testa
T: elementi lista coda

[H | T] = [a, b, c, d, e]: unificato la modalità di lettura della lista
- H = a
- T = [b, c, d, e]

[H | T] = [a]
- H = a
- T = []

[H | T] = [] // non se pò fa, non è unificabile
- H = 
- T = []

a $\in$ A ? dato un elelemento, possiamo scrivere un predicare che è vero se l'elemento appartiene all'insieme
`appartiene(X, L)`

Una lista puo essere vista come un elemento e una parte restante

L = [H | T]

due casi:
1. X unifica con H
2. `appartiene(X, T)`

appartiene(X, [1, 2, 3]) -> elenca gli elementi della lista

[H1, H1 | T] = [a, b, c]
- H1 = a
- H2 = b
- T = [c]
  
[H1, H1, T] = [a, b, c]
- H1 = a
- H2 = b
- T = c
  
rivoltata(L, RL) :- vera se RL è la lista L rovesciata

2+3+1=A+B = +(+(2, 3), 1) = +(A, B)

`A is 2 + 3` 
prima di unificare, `is` calcola la somma, poi unifica la somma as A

4 is 1 + 3
- true
4 is 3 + 2
- false

is fa due attivita diverse, sia di unificare sia di confronto (= and ==)

not -> =/=

`cut` (!): taglia un ramo di ricerca all interno dell albero dell alalgoritmo di risoluzione del prolog


`fail`: ci fa guardare un altro ramo


dato un predicato p :- a, b, c

se cut in tra a e b, una volta guardato a e sorpassato b, non posso tornare indietro ristanziando a. Non possiamo tornare indietro prima del cut. P puo essere verificato solo una volta. 

p :- d. non la posso utilizzare

## Definizione di nuovi operatori

:- op(priorità, K, nome)
dove k puo essere:
- fx
- xfx
- xfy
- yfx
la priorità deve essere decrescente

tutti gli operatori sono binari -> albero binario

vogliamo definire l'operatore somma, che deve comportarsi come +.

var(X), true se X è una variabile, false se è unificata
nonvar(X), true se X è unificato, false altrimenti.

X = 1,
var(X). -> false

X = 1,
nonvar(x). -> true

bagof(N, n(N), L) crea una lista con gli elementi letti con n()
setof(N, n(N), L) crea una lista/insieme gli elementi letti con n(), ordina pure.

setof(N, L^n(N, L), Lista).
L deve esistere ma non ci interessa il valore
voglio tutte le N per cui è vera n(N, L), e L non mi interessa.

setof(N, (L,B)^n(N, L, B), Lista).

## Esercitazione

1. 8 Regine

$x = (x_{i}, y_{i})$
$x = (x_{j}, y_{j})$

- $x_{i} \neq x_{j}$
- $y_{i} \neq y_{j}$
- $\nexists \delta\in (-k, k): (x_{i} = x_{j} + \delta \land y_{i} = y_{j} + \delta) \lor (x_{i} = - \delta \land y_{i} = y_{j} + \delta)$
