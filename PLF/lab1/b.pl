% Predicatul pentru a calcula CMMDC-ul prin scaderi repetate
% cmmdc(Numar1, Numar2, Rezultat)
cmmdc(Nr, 0, Nr) :- !.
cmmdc(0, Nr, Nr) :- !.

cmmdc(Nr1, Nr2, Result) :-
    Nr1 >= Nr2,
    Dif is Nr1 - Nr2,
    cmmdc(Dif, Nr2, Result).

cmmdc(Nr1, Nr2, Result) :-
    Nr1 < Nr2,
    Dif is Nr2 - Nr1,
    cmmdc(Nr1, Dif, Result).
