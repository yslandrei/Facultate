% adauga_pe_pozitia_n(l1...ln, e, p) = {
% 	e + l1...ln, daca p = 1
% 	l1 + adauga_pe_pozitia_n(l2...ln, e, p - 1), altfel
%}

% adauga_pe_pozitia_n(i, i, i, o)

adauga_pe_pozitia_n(L, E, 1, [E|L]):- !.
adauga_pe_pozitia_n([H|T], E, P, [H|R]):-
	P1 is P - 1,
	adauga_pe_pozitia_n(T, E, P1, R).
