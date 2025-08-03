% Enter the names of your group members below.
% If you only have 2 group members, leave the last space blank
%
%%%%%
%%%%% NAME: Brandon Aboukhater
%%%%% NAME: Derek Eliopoulos
%%%%% NAME: Kelvin Gu
%
% Add the required rules in the corresponding sections. 
% If you put the rules in the wrong sections, you will lose marks.
%
% You may add additional comments as you choose but DO NOT MODIFY the comment lines below
%

%%%%% SECTION: deepestNesting
%%%%% Predicate definition: deepestNesting(List, Depth)

% Base case: An empty list will have a depth = 0:
deepestNesting([], 0).

% Recursive General Case 1: If the head of the list is another list, call deepestNesting on it and the tail.
deepestNesting([Head|Tail], Depth) :-
    is_list(Head),
    deepestNesting(Head, Depth_Head),
    deepestNesting(Tail, Depth_Tail),
    Depth is max(Depth_Head + 1, Depth_Tail).

% Recursive General Case 2: If the head of the list is not a list, ignore it and call deepestNesting on the tail.
deepestNesting([Head|Tail], Depth) :-
    \+ is_list(Head),
    deepestNesting(Tail, Depth).









