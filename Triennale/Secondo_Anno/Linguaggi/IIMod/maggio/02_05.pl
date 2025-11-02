/*

Problema delle 8 Regine

*/

controlloRiga([A, B], [A, C]).

controlloColonna([A, B], [C, B]).

controlloDiagonale([A, B], [C, D]) :-
    X is A - C ,
    Y is B - D, 
    X =\= Y,
    X =\= -Y.

controlloCoppia([A]).
controlloCoppia([A, B|T]) :-
    controlloRiga(A, B),
    controlloColonna(A, B),
    controlloDiagonale(A, B),
    controlloCoppia([A|T]).

controlloSoluzione([A]).
controlloSoluzione([H|T]) :-
    \+controlloCoppia([H|T]),
    controlloSoluzione(T).

/*

Rompicapo del cavallo
Esercizio per casa
K >= 4 o 5

*/