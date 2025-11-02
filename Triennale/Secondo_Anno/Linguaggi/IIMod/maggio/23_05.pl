% multiplo3(A) :-
%    R is A // 3,
%    A is R * 3.  

% genera_falde(B1, B2, H, T) :-
%     multiplo3(B1),
%     multiplo3(B2),
%     multiplo3(H),
%     A is ((B1 + B2) * H) / 2,
%     T =.. [falda, B1, B2, H, A],
%     assert(T).

% length(X, 9) -> genera una lista di lunghezza 9
% length(X, 9), member(a, X) -> genera una lista di lunghezza 9 in cui prova a mettere a in tutte le posizioni


rettangolo(Base, 0, []).
rettangolo(Base, Altezza, [X|Rett]) :-
    Altezza > 0,
    length(X, Base),
    AltezzaMeno1 is Altezza - 1,
    rettangolo(Base, AltezzaMeno1, Rett).

pannello(a).
pannello(b).
pannello(c).
pannello(d).

lista_completa([]).
lista_completa([A|R]) :-
    nonvar(A),
    lista_completa(R).

lista_pannelli(Lungh, Lista) :-
    length(Lista, Lungh),
    lista_pannelli(Lista).

% lista_pannelli(Lista) :-
%     lista_completa(Lista).

% lista_pannelli(Lista) :-
%     pannello(X),
%     member(X, Lista),
%     lista_pannelli(Lista).

lista_pannelli([]).
lista_pannelli([X|Lista]) :-
    pannello(X),
    lista_pannelli(Lista).
    




