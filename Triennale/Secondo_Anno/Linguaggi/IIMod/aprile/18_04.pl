/*
-- Torri di Hanoi
*/

ord([]).
ord([_]).
ord([H1, H2|T]) :-
    H1 < H2,
    ord([H2|T]).

edge(h([X|A], B, C), h(A, [X|B], C)) :-
    ord([X|A]), 
    ord([X|B]),
    ord(C).

edge(h(A, [X|B], C), h(A, B, [X|C])) :-
    ord([X|B]), 
    ord([X|C]),
    ord(A).

parcheggi([A1, A2, A3,
           A4, A5, A6,
           A7, A8, E], [A1, A2, A3, A4, A5, E, A7, A8, A6]).






