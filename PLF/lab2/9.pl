% 9.a

% Model matematic:
% remConsecutive(l1...ln) =
% 	l1...ln, n <= 1
% 	[], n = 2 si l2 = l1 + 1
% 	remConsecutive(l2...ln), l2 = l1 + 1 si l3 = l2 + 1
% 	remConsecutive(l3...ln), l2 = l1 + 1 si l3 != l2 + 1
% 	l1 + remConsecutive(l2...ln), l2 != l1 + 1

% Model de flux: remConsecutive(i, o)

remConsecutive([], []).
remConsecutive([E], [E]).
remConsecutive([H1, H2], []) :- H2 =:= H1 + 1.
remConsecutive([H1, H2], [H1, H2]) :- H2 =\= H1 + 1.
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =:= H2 + 1,
    remConsecutive([H2, H3|T], R).
remConsecutive([H1, H2, H3|T], R) :- 
    H2 =:= H1 + 1,
    H3 =\= H2 + 1,
    remConsecutive([H3|T], R).
remConsecutive([H1, H2, H3|T], [H1|R]) :- 
    H2 =\= H1 + 1,
    remConsecutive([H2,H3|T], R).

% 9.b

% Model matematic:
% heterList(l1...ln) = 
% 	[], n = 0
% 	remConsecutive(l1) + heterList(l2...ln), is_list(l1) = True
% 	l1 + heterList(l2...ln), altfel

% Model de flux: heterList(i, o)

heterList([], []).
heterList([H|T], [HR|R]) :- is_list(H), !,
    remConsecutive(H, HR),
    heterList(T, R).
heterList([H|T], [H|R]) :-
    heterList(T, R).




remConsecutive2([], []).
remConsecutive2([E], [E]).
remConsecutive2([H1, H2], []) :- H2 =:= H1 + 1.
remConsecutive2([H1, H2], [H1, H2]) :- H2 =\= H1 + 1.
remConsecutive2([H1, H2|T], R) :- 
    H2 =:= H1 + 1,
    remConsecutive([H2|T], R).
remConsecutive2([H1, H2|T], [H1|R]) :- 
    H2 =\= H1 + 1,
    remConsecutive([H2|T], R).

