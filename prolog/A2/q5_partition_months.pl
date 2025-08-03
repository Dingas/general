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

is_empty([]).

partitionMonths([], [], [], []).
partitionMonths([_], [_], [], []).

partitionMonths([Month1, Month2 | RestMonths], [Price1, Price2 | RestPrices], [Month2 | Increase], Decrease) :-
    Price2 >= Price1, % Stock price increased or stayed the same.
    partitionMonths([Month2 | RestMonths], [Price2 | RestPrices], Increase, Decrease).

partitionMonths([Month1, Month2 | RestMonths], [Price1, Price2 | RestPrices], Increase, [Month2 | Decrease]) :-
    Price2 < Price1, % Stock price decreased.
    partitionMonths([Month2 | RestMonths], [Price2 | RestPrices], Increase, Decrease).

partitionMonths(Months, Prices, Increase, Decrease) :-
    partitionMonths(Months, Prices, Increase, Decrease).

%%%%% SECTION: partitionMonths
%%%%% Predicate definition: partitionMonths(Months, Prices, Increase, Decrease)
