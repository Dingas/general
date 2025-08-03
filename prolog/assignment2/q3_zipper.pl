% Enter the names of your group members below.
% If you only have 2 group members, leave the last space blank
%
%%%%%
%%%%% NAME: Kelvin Gu
%%%%% NAME: Brandon Aboukhater
%%%%% NAME: Derek Eliopoulos
%
% Add the required rules in the corresponding sections. 
% If you put the rules in the wrong sections, you will lose marks.
%
% You may add additional comments as you choose but DO NOT MODIFY the comment lines below
%

%%%%% SECTION: zipper
%%%%% Predicate definition: zipper(List1, List2, Zipper)
zipper([], List2, List2).
zipper(List1, [], List1).
zipper([H1 | T1], [H2 | T2], [H1, H2 | TZip]) :- zipper(T1, T2, TZip).
