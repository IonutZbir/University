% member(L, Elem)
my_member([X|_], X). % sta in testa
my_member([X|T], X) :- % sta in coda
    my_member(T, X).

% append(L1, L2, L12)

my_append([], L, L).
my_append([H|T], L, [H|T1]) :-
    my_append(T, L, T1).

% reverse(L, RL)
my_reverse([], []).
my_reverse([Head|Tail], RList) :-
    my_append(RTail, [Head], RList),
    my_reverse(RTail, RList).

% permutation(L, PM)
my_permutation([], []).
my_permutation([H|T], L2) :-
    my_permutation(T, L3),
    my_member(L2, H),
    subtract(L2, H, L3).
    
my_len([], 0).
my_len([H|T], X):-
    my_len(T, Y),
    X is Y + 1.

my_ord([], []).
my_ord([H1|T1], [H2|T2]) :-
    H1 > H2, % <
    my_ord(T1, T2).


/*
Partiamo da "haStessaStruttura", che ha come argomenti 2 liste. 
Se abbiamo due predicati del tipo:
a(N, M) :-
    b(N, K),
    c(K, M).

gda(N, M) :-
    gdb(N, K).

Allora H1 e H2 sono a(N, M) e rispettivamente gda(N, M). Dopo di che controllo il numero di componenti, se sono uguali allora 
chiamo "controlloPredicati". Verifico adesso che i due fatti, H1 e H2 abbiano lo stesso numeoro di argomenti e induttivamente
chiamo "controlloPredicati" sul resto delle componenti.

*/