% Enter the names of your group members below.
% If you only have 2 group members, leave the last space blank
%
%%%%%
%%%%% NAME: Derek Eliopoulos
%%%%% NAME: Kelvin Gu
%%%%% NAME: Brandon Aboukhater
%
% Add the required rules in the corresponding sections. 
% If you put the rules in the wrong sections, you will lose marks.
%
% You may add additional comments as you choose but DO NOT MODIFY the comment lines below
%

%%%%% SECTION: appendT
%%%%% Add your rules for appendT(Term1,Term2,Result) below

appendT(nil, Term2, Term2).
appendT(next(Head, Tail), Term2, next(Head, Result)) :- appendT(Tail, Term2, Result).

%%%%% SECTION: list2term
%%%%% Add your rules for list2term(List,Term) below

list2term([], nil).
list2term([Head|Tail], next(HeadTerm, TailTerm)) :- 
    (is_list(Head) -> list2term(Head, HeadTerm); HeadTerm = Head),
    list2term(Tail, TailTerm).

%%%%% SECTION: flat
%%%%% Add your rules for flat(Term,FlatTerm) below

flat(nil, nil).
flat(next(Head, Tail), FlatTerm) :-
    (is_list(Head) -> flat(Head, HeadFlat); HeadFlat = Head),
    flat(Tail, TailFlat),
    appendT(HeadFlat, TailFlat, FlatTerm).
