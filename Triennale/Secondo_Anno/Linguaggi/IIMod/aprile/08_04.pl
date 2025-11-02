:- dynamic fib/2.

fib(1, 1) :-
    !.
fib(2, 1) :-
    !.
fib(N, M) :-
    write(in),nl,
    X is N-1,
    Y is N-2,
    X > 0,
    Y > 0,
    fib(X, A),
    fib(Y, B),
    M is A + B,
    asserta(fib(N, M) :- !).
