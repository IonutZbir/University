% genitore(parent, child)

% fatti
genitore(mario, dario).
genitore(mario, gino).
genitore(pino, rino).
genitore(luca, pino).

% predicati
fratello(X, Y) :- 
    genitore(Z, X),
    genitore(Z, Y).

nonno(X, Y) :- 
    genitore(X, Z), 
    genitore(Z, Y).

% induzione 
avo(X, Y) :-
    genitore(X, Y).
avo(X, Y) :-
    genitore(X, Z), 
    avo(Z, Y).
