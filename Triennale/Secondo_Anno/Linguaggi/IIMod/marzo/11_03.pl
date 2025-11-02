% fatti
edge(a, b).
edge(a, e).
edge(b, c).
edge(e, f).
edge(f, c).
edge(c, d).
edge(f, k).
edge(c, a).
edge(c, d).
edge(d, a).

% predicati 
path(X, Y) :- % caso base
    edge(X, Y).
path(X, Y) :- % se esiste un nodo Z tale che esiste un arco da X a Z ed esite un percorso da Z a Y
    edge(X, Z),
    path(Z, Y).

% nell'induzione, prima il caso base, poi nel caso induttivo, mettere prima il goal base e poi il predicato
% dobbiamo stare attenti a come impostiamo i goal per la risoluzione del predicato!
cycle(X) :-
    edge(X, Y),
    edge(Y, X).
cycle(X) :-
    edge(X, Y),
    path(Y, X).
