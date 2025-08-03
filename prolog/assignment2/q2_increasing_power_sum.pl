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

%%%%% SECTION: increasingPowerSum
%%%%% Predicate definition: increasingPowerSum(List, Power, PowerInc, Sum)

% Base case when the list is empty, empty list will always have 0 sum

increasingPowerSum([], _, _, 0).

% Recursive case when the list is not empty
% We can use the head and tail properties of the list to perform our recursive summing, get the result of the head
% and call the function again with the tail while keeping track of the sum.
% We can also use the PowerInc variable to keep track of the power increment

increasingPowerSum([H|T], Power, PowerInc, Sum) :-
    NewPower is Power + PowerInc,                 
    increasingPowerSum(T, NewPower, PowerInc, NewSum),  
    Sum is H^Power + NewSum.  




    


