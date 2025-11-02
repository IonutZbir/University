/*
Abbiamo individuato un business molto interessante: vendere sogni alle persone. Si vuol far credere che il 
futuro delle persone dipenda dall’uso delle vocali all’interno dell’oroscopo per il loro segno zoodiacale. La 
giornata è positiva se nell’oroscopo il la frequenza media delle vocali è esattamente uguale alla frequenza 
media delle consonanti. 
Si vuole dunque definire un predicato prolog che consenta di calcolare la frequenza media delle vocali e 
quella delle consonanti e di un altro che poi permetta di dire se una giornata è fortunata
*/

vocale("a").
vocale("e").
vocale("i").
vocale("o").
vocale("u").

mynot(Predicato) :-
    Predicato, !, fail.
mynot(_).

getLen([], 0).
getLen([_|T], L) :-
    getLen(T, M),
    L is M + 1.

getVocali([], 0).
getVocali([H|T], V) :-
    vocale(H),!,
    getVocali(T, V2),
    V is V2 + 1. 
getVocali([_|T], N) :-
    getVocali(T, N).

getCons([], 0).
getCons([H|T], C) :-
    mynot(vocale(H)),
    getCons(T, C2),
    C is C2 + 1.
getCons([_|T], N) :-
    getCons(T, N).

media(S) :-
    getCons(S, C),
    getVocali(S, V),
    getLen(S, L),
    write(C), nl, write(V), nl, write(L),
    D is C / 16,
    D is V / 5.

giornata(S) :-
    media(S),
    write("Giornata Fortunata").
