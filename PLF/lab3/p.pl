% M% odel matematic:

% replaceEl(l1...ln, e1, e2) =
%       [], n = 0
%       e2 + replaceEl(l2...ln, e1, e2), l1 = e1
%       l1 + replaceEl(l2...ln, e1, e2), otherwise

% flow: replaceEl(i, i, i, o)

replaceEl([], _, _, []).
replaceEl([H|T], E1, E2, [E2|R]) :- H =:= E1, !,
    replaceEl(T, E1, E2, R).
replaceEl([H|T], E1, E2, [H|R]) :-
    replaceEl(T, E1, E2, R).

% b

% Model matematic:
% maxim_number(a, b) =
%       a, a >= b
%       b a < b

% maxim_number(i, i, o)

maxim_number(A, B, A) :- A >= B.
maxim_number(A, B, B) :- A < B.

% Model matematic:
% maxim_list(l1...ln) =
%       l1, n = 1
%       maxim_number(l1, maxim_list(l2...ln)), number(l1) = True
%        maxim_list(l2...ln), otherwise

% maxim_list(L:list, R:number)
% maxim_list(i, o)

maxim_list([H], H).
maxim_list([H|T], R) :- number(H), !,
    maxim_list(T, RM),
    maxim_number(H, RM, R).
maxim_list([_|T], R) :-
    maxim_list(T, R).

% Model matematic:
% heterList(l1...ln, m) =
%       [], n = 0
% replaceEl(l1, m, maxim_list(l1)) + heterList(l2...ln, m), is_list(l1) = True

%       l1 + heterList(l2...ln, m), otherwise

% flow : heterList(i, o)

%htlist - prima clauza verifica daca primul element din lista este numar, caz in care calculeaza maximul acelei liste si inlocuieste M din heterlist cu acel maxim
% a doua clauza face cazul contrar, caz in care pur si simplu continua recursivitatea
heterList([], _, []).
heterList([H|T], M, [HR|R]) :- is_list(H), !,
    maxim_list(H, RM),
    replaceEl(H, M, RM, HR),
    heterList(T, M, R).
heterList([H|T], M, [H|R]) :-
    heterList(T, M, R).

% flow : heterList(i, o)

mainHeter(L, R) :-
    maxim_list(L, RM),
    heterList(L, RM, R).
