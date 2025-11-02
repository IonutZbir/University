f(b).
f(a).
g(a).
g(b).
g(j).
k(a).

p(A) :-
    f(A),
    write("10: "), write(A), nl,
    !,
    g(A),
    write("13: "), write(A), nl,
    k(A).

/* Negation as failure */

mynot(Predicato) :-
    Predicato, !, fail.
mynot(_).

/* ha senso il porco dio di cut, ma limitiamo gli utilizzi del cut, anche con il diverso di merda */

numDiEl(_, [], 0).
numDiEl(X, [X|T], N) :-
    !,
    numDiEl(X, T, N1),
    N is N1 + 1.
numDiEl(X, [_|T], N) :-
    /* \+ (X = Y),  X != Y */
    /* usando bene il cut, possiamo fare a meno del diverso */
    numDiEl(X, T, N).


