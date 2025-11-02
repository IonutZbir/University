/* contex free di chomsky
L contenuto in sigma star
scopo è generare e riconoscere un linguaggio
data una stringa dire se appartiene al lingu
sigma = {a, b}
 

    A -> BC
        B -> a
        C -> b
        A -> C B B 


A è lo start simbol, S sta per sentence

derivazione, sinistra a destra */


produzioneA(L, R1):-
    produzioneC(L, R),
    produzioneBB(R, R1).

produzioneBB(L, R1):-
    produzioneB(L, R),
    produzioneB(R, R1).

produzioneB([a|R], R).
produzioneC([b|R], R).


'A' --> 'B', 'C'.
'A' --> 'C', 'B', 'B'.
'B' --> [a].
'C' --> [b].

/*
A(L, R1):-
 	B(L, R),
 	C(R, R1).
*/