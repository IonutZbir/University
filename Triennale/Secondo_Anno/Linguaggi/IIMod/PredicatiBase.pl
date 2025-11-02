/* 
    member(Elem, List).

    Dato un elemento Elem, se appartiene alla lista List, allora True.

    Nota: Esiste già come predicato
*/

my_member(Elem, [Elem|_]). 
my_member(Elem, [_|T]) :-
    my_member(Elem, T).

/*
    O sta in testa, oppure sta in coda
*/

/*
    append(List1, List2, List1AndList2).

    List1AndList2 è la concatenazione di List1 e List2

    Nota: Esiste già come predicato
*/

my_append([], List2, List2).
my_append([X|Xs], List2, [X|Zs]) :-
    my_append(Xs, List2, Zs).

/*
    reverse(List, RList).

    RList è la lista rivoltata di List

    Nota: Esiste già come predicato
*/

my_reverse([], []).
my_reverse([Head|Tail], RList) :-
    my_append(RTail, [Head], RList),
    my_reverse(Tail, RTail).

/*
    Costruisco la lista rivoltata man mano, inizialmente concateno il primo elemento e cosi via finché non 
    ottengo la lista rivoltata. Concateno alla coda rivoltata il primo elemento in testa alla lista, costruendo cosi
    la lista finale.
*/

/*
    subtract(List, Del, Result).

    Elimina Del dalla List e ottiene Result

    Nota: Esiste già come predicato
*/

my_subtract([], _, []).
my_subtract([H|T], H, T).
my_subtract([X|T], H, [X|R]) :-
    my_subtract(T, H, R).

/*
    - Da una lista vuota, qualsiasi elemento devo cancellare, ottengo una lista vuota.
        [], a, []
    - Da una lista, se l'elemento da cancellare si trova in testa H, lo cancello e ottengo il restante T.
        [a, b, c], a, [b, c]
    - Da una lista, se l'elemento da cancella non si trova in testa, allora sta nella coda, e lo devo cancellare da lì. 
        Ovviamente, la lista risultante deve inziare con lo stesso elemento della lista iniziale.
        [a, b, c], b, [a, c]
*/

/*
    permutation(List1, List2).

    List2 è una permutazione di List1

    Nota: Esiste già come predicato
*/

my_permutation([], []).
my_permutation([H|T], List2) :-
    my_permutation(T, List3),
    my_member(H, List2),
    my_subtract(List2, H, List3).

/*
    - La permutazione di una lista vuota, è una lista vuota.
    - La permutazione di una lista, è un qualsiasi ordinamento degli elementi della lista inziale.
    Prima chiedo una permutazione della coda, poi controllo che il primo elemento appartiene alla permutazione e infine
    lo tolgo, perche una volta ottenuta una permutazione che include quel elemento, non posso piu utilizzarlo.
    [!NOTA] Ricordare il disegno fatto in classe da znz8
*/

/*
    lenght(List, Len)

    Len è il numero di elementi della lista List

    Nota: Esiste già come predicato
*/

my_length([], 0).
my_length([_|T], Len) :-
    my_length(T, Len1),
    Len is Len1 + 1.

/*
    repeat(List, Elem, N)

    N è il numero di volte che Elem si ripete in List
*/

repeat([], _, 0).
repeat([Elem|T], Elem, N) :-
    repeat(T, Elem, N1),
    N is N1 + 1.
repeat([H|T], Elem, N) :-
    H \= Elem,
    repeat(T, Elem, N). 

repeat_cut([], _, 0).
repeat_cut([Elem|T], Elem, N) :-
    !,
    repeat_cut(T, Elem, N1),
    N is N1 + 1.
repeat_cut([_|T], Elem, N) :-
    repeat_cut(T, Elem, N).

/*
    Operatore Logico NOT
*/

my_not(Predicato) :-
    Predicato,
    !,
    fail.
my_not(_).
