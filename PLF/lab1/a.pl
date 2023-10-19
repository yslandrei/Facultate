% Predicatul pentru a insera un element la o anumita pozitie intr-o lista
% insert_element(ListaInitiala, Pozitie, Element, ListaRezultata)
insert_element(List, Pos, Elem, Result) :-
    insert_element_acc(List, Pos, Elem, 1, Result).

% insert_element_acc(Lista, Pozitie, Element, Index, ListaRezultata)
insert_element_acc([], Pos, Elem, Pos, [Elem]).
insert_element_acc([H|T], Pos, Elem, Pos, [Elem,H|T]).
insert_element_acc([H|T], Pos, Elem, Index, [H|Result]) :-
    NewIndex is Index + 1,
    insert_element_acc(T, Pos, Elem, NewIndex, Result).

% Exemplu de utilizare:
% ?- insert_element([1,2,3,4,5], 3, 100, Result).
% Result = [1, 2, 100, 3, 4, 5].

