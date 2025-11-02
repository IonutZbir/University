appartiene(X, [X|_]). /* X appartiene alla Testa? */
appartiene(X, [_|T]) :- /* X appartiene alla Coda? */
    appartiene(X, T).

concatenazione([], A, A).
concatenazione([H|T], B, [H|L]) :-
    concatenazione(T, B, L).

rivoltata([], []).
rivoltata([H|T], RL) :- 
    concatenazione(RT, [H], RL), /*Creo RL è la coda rivoltata concatenta la testa*/ 
	rivoltata(T, RT).
    
sottratto(_, [], []). /* H puo non appartene, se lo tolgo H deve appartenere alla lista */
sottratto(H, [H|R], R).
sottratto(H, [A|R1], [A|R2]) :-
    sottratto(H, R1, R2).
	
permutazione([], []).
permutazione([H|T], B) :-
    permutazione(T, PT1_2), /* PT1_2 = B - H */
    appartiene(H, B),
    sottratto(H, B, PT1_2).


