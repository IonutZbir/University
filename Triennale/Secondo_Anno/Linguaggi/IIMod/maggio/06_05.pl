/*
    edge(A, B)
*/

/*
    path(X, Y, PATH)
*/

/*
    estendere per fare in modo che non visito due volte lo stesso modo
*/

edge(a, b).
edge(a, c).
edge(b, c).
edge(k, f).
edge(c, d).
edge(d, e).

% DFS
pathDFS(X, Y, [X|Y]) :-
    edge(X, Y).
pathDFS(X, Y, [X|P_Z_Y]) :-
    edge(X, Z),
    pathDFS(Z, Y, P_Z_Y).

% BFS
/*
    pf(F, PF) vero se F è una frontiera, e PF è raggiungibile da F
*/

pf([], []).
pf([H|T], F) :-
    setof(Z, edge(H, Z), RAG_Z),
    pf(T, PF),
    % append(suffisso, prefisso, suffissoPrefisso)
    append(RAG_Z, PF, F).

pathBFS(X, Y) :-
    opf([X], FF, Y). % se esiste una frontiera in cui c'e Y raggiungibile da [X]

opf(F, FR, Y) :-
    pf(F, FR),
    member(Y, FR).
opf(F, FR, Y) :-
    pf(F, FRZ),
    opf(FRZ, FR, Y).

/* DA FINIRE    
pf([[X|PX]|T], F) :-
    setof([Z|[X|PX]], edge(X, Z), RAG_Z)
*/