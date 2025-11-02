:- dynamic appoggio/1.

n(11, a, la).
n(2, a, da).
n(4, a, ds).
n(5, a, lf).
n(5, a, fe).
n(8, a, sd).
n(5, a, fv).
n(8, a, vh).

len_lista([], 0).
len_lista([_|T], N) :-
    len_lista(T, M),
    M >= 0,
    N is 1 + M.

numero_lettere_diverse(N) :- % vero se N è il numero di lettere diverse nella seconda poszione dei fatti sopra
    setof(L, (N, B)^n(N, L, B), Lista),
    % write(Lista),nl,
len_lista(Lista, N). %length(Lista, N).
/*
num(L) :-
    n(L, _).
Predicato numeri
numeri(L) se ci sono i numeri di quei fatti 
L è un lista
cut, fail, assert, retract
*/
/*
appoggio([]).

numeri(L) :- % torna true se L = [11, 1, 3, 7, 11]
    n(Num),
    appoggio(L),
    append(L, [Num], LN),
    retract(appoggio(L)),
    assert(appoggio(LN)),
    write(Num),nl,
    fail.
numeri(L) :-
    appoggio(L),
    retract(appoggio(L)),
    assert(appoggio([])).
*/
