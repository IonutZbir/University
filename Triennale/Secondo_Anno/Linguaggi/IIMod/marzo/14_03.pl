appartiene(X, [X|_]). /* X appartiene alla Testa? */
appartiene(X, [_|T]) :- /* X appartiene alla Coda? */
    appartiene(X, T).

concatenazione([], A, A).
concatenazione([H|T], B, [H|L]) :- /* concat(A, B, C), C è la concatenazione di A e B se C inzia con H e L e la concatenazione di T e B */
	concatenazione(T, B, L).

