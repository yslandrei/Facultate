% subseturi(l1...ln) =
% 	[], daca n = 0
% 	l1 + subseturi(l2...ln), daca n > 0
% 	subseturi(l2...ln), daca n > 0
%
% subseturi(L:lista, R:lista)
% subseturi(i, o)

subseturi([], []).
subseturi([H|T], [H|R]) :-
    subseturi(T, R).
subseturi([_|T], R) :-
    subseturi(T, R).

% suma(l1...ln, c) =
% 	c, daca n = 0
% 	suma(l2...ln, c + l1), altfel

% suma(L:lista, C:numar, R:numar)
% suma(i, i, o)

suma([], C, C).
suma([H|T], C, R) :
    NC is C + H,
    suma(T, NC, R).

% verif(l1...ln, n) =
% 	true, daca suma(l1...ln, 0) % n = 0
% 	false, altfel

% verif(L:lista, N:numar)
% verif(i, i)

verif(L, S) :-
    suma(L, 0, S).

% solutie(L:lista, N:numar, R:lista)
% solutie(i, i, o)

solutie(L, S, R) :- 
    subseturi(L, R),
    suma(R, 0, S).

% toate_solutile(L:lista, S:numar, R:lista)
% toate_solutile(i, i, o)

toate_solutile(L, S, R) :-
    findall(RPartial, solutie(L, S, RPartial), R).
