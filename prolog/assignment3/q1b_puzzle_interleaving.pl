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

%%%%% SECTION: puzzleGenerateAndTest
%%%%% Below, you should define rules for the predicate "solve", which takes in your list of
%%%%% variables and finds an assignment for each variable which solves the problem.
%%%%%
%%%%% You should also define rules for the predicate "solve_and_print" which calls your
%%%%% solve predicate and prints out the results in an easy to read, human readable format.
%%%%% The predicate "solve_and_print" should take in no arguments
    
equal(X, X).
equal(X, Y) :- Z is X - Y, 0 is Z * Z.

dig(X) :- member(X, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]).

all_different([]).
all_different([H|T]) :- not(member(H, T)), all_different(T).    

solve([A, E, I, L, O, P, S, T, V]) :-

    dig(L), L > 0,
    dig(E),                                %Prune the search space progressively as we step through the constraints                 
    dig(T), T > 0,                         %Only instantiates L, E, T first, making sure leading digits are not 0

    all_different([L, E, T]),              %Check right away if they are all different before moving on      

    LET is L*100 + E*10 + T,

    dig(A), A > 0,                         %If the above constraints are satisfied, then we can instantiate A, P, and S
    dig(P),

    all_different([L, E, T, A, P]),        %Again check if they are all unique before moving on      

    LAP is L*100 + A*10 + P,
    PRODUCT is LET * LAP,                  %Calculate the product of LET and LAP immediately

    dig(I), I > 0,                         %If the above constraints are satisfied, then we can instantiate I, S, and later V and O
    dig(S),                                                 

    all_different([L, E, T, A, P, I, S]),

    ITS is I*100 + T*10 + S,

    dig(O),
    dig(V),

    all_different([A, E, I, L, O, P, S, T, V]), %Finally check that they are all distinct
    
    LOVE is L*1000 + O*100 + V*10 + E,
    SUM is ITS + 10*LOVE + 100*LET,

    equal(PRODUCT, SUM),                  %Check if the product and sum are equal right away

    TOOLS is T*10000 + O*1000 + O*100 + L*10 + S,
    equal(TOOLS, SUM).

     
solve_and_print :-

    solve([A, E, I, L, O, P, S, T, V]),
    write('    '), write(L), write(' '), write(E), write(' '), write(T), nl,
    write('  * '), write(L), write(' '), write(A), write(' '), write(P), nl,
    write('  '), write('----------'), nl,
    write('    '), write(I), write(' '), write(T), write(' '), write(S), nl,
    write('+ '), write(L), write(' '), write(O), write(' '), write(V), write(' '), write(E), nl,
    write('  '), write(L), write(' '), write(E), write(' '), write(T), write(' '), nl,
    write('  '), write('----------'), nl,
    write(' '), write(T), write(' '), write(O), write(' '), write(O), write(' '), write(L), write(' '), write(S), nl.
    
    