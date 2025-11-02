:- dynamic mossa/2.

mossa(a, b).

controlloMossa(Xi, Xj, Yi, Yj) :-
    2 is abs(Xi - Xj),
    1 is abs(Yi - Yj).

controlloMossa(Xi, Xj, Yi, Yj) :-
    1 is abs(Xi - Xj),
    2 is abs(Yi - Yj).

controlloSoluzione([[X, Y]]) :-
    \+mossa(X, Y),
    assert(mossa(X, Y)).
    %retractall(mossa(_, _)).

controlloSoluzione([[Xi, Yi], [Xj, Yj]|T]) :-
    \+mossa(Xj, Yj),
    write("("),write(Xi), write(", "), write(Yi), write("); ("),
    write(Xj), write(", "), write(Yj), write(") "), nl,
    controlloMossa(Xi, Xj, Yi, Yj),
    assert(mossa(Xi, Yi)),
    controlloSoluzione([[Xj, Yj]|T]),
    retractall(mossa(_, _)),!.
controlloSoluzione([_|_]) :-
    retractall(mossa(_, _)),
    fail.

    