lung([], 0).
lung([_|T], L) :-
    lung(T, A),
    A >= 0,
	L is 1 + A.

/*numero N di volte che E appare in L*/
numeroDiEl([], _, 0).
numeroDiEl([E|T], E, N) :-
    numeroDiEl(T, E, M),
    N is 1 + M.
numeroDiEl([X|T], E, M) :- /*vero se in testa c'è un qualsiasi elemento*/
    X \= E,
    numeroDiEl(T, E, M).
    
