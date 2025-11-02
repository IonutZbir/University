/* tree(R, Children) */
/* R(Children) =..[] */
/* leaf(T, L) :- */
/* vero se L è una foglia di T, e T è un albero */

/* 
somma(T, S) :-
    T =.. [t, A, B],
    S is A + B.
*/

/* 
t(a,
    [t(b,
        [t(a, []),
        t(b, [])]),
    t(c, []),
    t(d, [])])

    t(Root, Children)
*/

/*
get_vocali(t("a",
    [t("b",
        [t("a", []),
        t("b", [])]),
    t("c", []),
    t("d", [])]), X).
*/

somma(t(X, Y), S) :-
    S is X + Y.

/*
leaf(T, R) :-
    T =.. [T, []].
leaf(T, L) :-
    T =.. [_, Children],
    memeber(C, Children),
    leaf(C, Children).
*/

vocale("a").
vocale("e").
vocale("i").
vocale("o").
vocale("u").

get_vocali([],0). % lista vuota
get_vocali(t(R,[]), 1):- % foglia si
    vocale(R).
get_vocali(t(R,[]), 0):- % oglia no
    \+vocale(R).
get_vocali(t(A,Child),M):- % nodo si
    vocale(A),!,
    get_vocali(Child,N),
    M is N+1.
get_vocali(t(A,Child),M):- % nodo no
    \+vocale(A),!,
    get_vocali(Child,M).
get_vocali([H|T],M):-
    get_vocali(H,A),!,
    get_vocali(T,B),!,
    M is A+B.

/*
get_vocali(t(R, []), 1) :-
    vocale(R).
get_vocali(t(R, Children), X1) :-
    vocale(R),
    get_vocali_in_children(Children, X),
    X1 is X + 1.
get_vocali(t(_, Children), X1) :-
    get_vocali_in_children(Children, X1).

get_vocali_in_children([], 0).
get_vocali_in_children([C|Cs], X) :-
    get_vocali(C, X1),
    get_vocali_in_children(Cs, X2),
    X is X1 + X2.
*/

leaf(t(R, []), R).
leaf(t(_, Children), L) :-
    member(C, Children), % per ciascun nodo C all interno di Children
    leaf(C, L). % verifica se è una foglia

node(t(R, _), R).
node(t(_, Children), L) :-
    member(C, Children),
    node(C, L).
