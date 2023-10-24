% cmmdc(a, b) = {
%	  a, b = 0
%	  b, a = 0
%	  cmmdc(a % b, b), daca a >= b
%	  cmmdc(a, b % a), daca a < b
% }

% cmmdc(i, i, o)

cmmdc(0, B, B) :- !.
cmmdc(A, 0, A) :- !.
cmmdc(A, B, R) :- 
  A >= B,
  A1 is A mod B,
  cmmdc(A1, B, R), !.
cmmdc(A, B, R) :- 
	A < B,
  B1 is B mod A,
  cmmdc(A, B1, R), !.

% cmmdc_pe_lista(l1...ln) = {
%   l1, daca n = 1
%   cmmdc(l1, cmmdc_pe_lista(l2...ln)), altfel
% }

% cmmdc_pe_lista(i, o)
  
cmmdc_pe_lista([H], H).
cmmdc_pe_lista([H|T], R) :- 
  cmmdc_pe_lista(T, R1),
  cmmdc(R1, H, R).
