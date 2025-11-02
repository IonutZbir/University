% P01 (*) Find the last element of a list.

my_last(X, [X]).
my_last(X, [_|T]) :-
    my_last(X, T).

% P02 (*) Find the last but one element of a list.

last_but_one(X, [X, _]).
last_but_one(X, [_| T]) :-
    last_but_one(X, T).

% P03 (*) Find the Kth element of a list.

element_at(X, [X|_], 1).
element_at(X, [_|T], K) :-
    K > 1,
    K1 is K - 1,
    write(K1), nl,
    element_at(X, T, K1).

% P04 (*) Find the number of elements of a list.

my_length([], 0).
my_length([_|T], N) :-
    my_length(T, N1),
    N is N1 + 1.

% P05 (*) Reverse a list.

my_reverse(L1, L2) :-
    my_rev(L1, L2, []).

my_rev([] , L2, L2) :- !.
my_rev([X|Xs], L2, Acc) :-
    my_rev(Xs, L2, [X|Acc]).

% P06 (*) Find out whether a list is a palindrome.

is_palindrome([]).
is_palindrome(L) :- 
    my_reverse(L, L).

% P07 (**) Flatten a nested list structure.

% Example: 
% ?- my_flatten([a, [b, [c, d], e]], X).
% X = [a, b, c, d, e]

my_flatten(X, [X]) :- 
    \+ is_list(X).
my_flatten([], []).
my_flatten([H|T], L) :- 
    my_flatten(H, L1),
    my_flatten(T, L2),
    append(L1, L2, L).

% P08 (**) Eliminate consecutive duplicates of list elements.

% Example:
% ?- compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [a,b,c,a,d,e]

compress([], []).
compress([X], [X]).
compress([H, H|T], L) :-
    compress([H|T], L).
compress([H1, H2|T1], [H1| T]) :-
    H1 \= H2,
    compress([H2|T1], T).

% P09 (**) Pack consecutive duplicates of list elements into sublists.

% Example:
% ?- pack([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [[a,a,a,a],[b],[c,c],[a,a],[d],[e,e,e,e]]

pack([],[]).
pack([X|Xs],[Z|Zs]) :- 
    transfer(X,Xs,Ys,Z), 
    pack(Ys,Zs).

% transfer(X,Xs,Ys,Z) Ys is the list that remains from the list Xs
% when all leading copies of X are removed and transfered to Z

transfer(X,[],[],[X]).
transfer(X,[Y|Ys],[Y|Ys],[X]) :-
    X \= Y.
transfer(X,[X|Xs],Ys,[X|Zs]) :- 
    transfer(X,Xs,Ys,Zs).

% P10 (*) Run-length encoding of a list.

% Example:
% ?- encode([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [[4,a],[1,b],[2,c],[2,a],[1,d],[4,e]]

encode(L1, L2) :-
    pack(L1, X),
    compress_every_sublist(X, L2).

compress_every_sublist([], []).
compress_every_sublist([[X|Xs]|Ys], [[N,X]|Zs]) :-
    my_length([X|Xs], N),
    compress_every_sublist(Ys, Zs).


