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

   dig(A), dig(E), dig(I), dig(L), dig(O), dig(P), dig(S), dig(T), dig(V),

    % No leading zeros
    L > 0, I > 0, T > 0,

    % All digits must be different
    all_different([A, E, I, L, O, P, S, T, V]),

    LET is L*100 + E*10 + T,
    LAP is L*100 + A*10 + P,
    ITS is I*100 + T*10 + S,
    LOVE is L*1000 + O*100 + V*10 + E,
    TOOLS is T*10000 + O*1000 + O*100 + L*10 + S,
    PRODUCT is LET * LAP,
    SUM is ITS + 10*LOVE + 100*LET,
    equal(PRODUCT, SUM),
    equal(TOOLS, SUM).


    
    % S is P * T mod 10, C1 is P * T // 10,

    % (100 * L + 10 * E + T) * (100 * L + 10 * A + P) =:= 10000 * T + 1000 * O + 100 * O + 10 * L + S. 

    % ITS + 10 * LOVE + 100 * LET = TOOLS
    %(100 * I + 10 * T + S) + (1000 * L + 100 * O + 10 * V + E) + (10000 * L + 1000 * E + 100 * T) =:= 10000 * T + 1000 * O + 100 * O + 10 * L + S.

    % LET * P
    % P1 is P * T, S1 is P1 mod 10, PC1 is P1 // 10,
    % P10 is P * E + PC1, T1 is P10 mod 10, PC10 is P10 // 10,
    % P100 is P * L + PC10, I1 is P100 mod 10, PC100 is P100 // 10,

    % % LET * A
    % A1 is A * T, E1 is A1 mod 10, AC1 is A1 // 10,
    % A10 is A * E + AC1, V1 is A10 mod 10, AC10 is A10 // 10,
    % A100 is A * L + AC10, O1 is A100 mod 10, AC100 is A100 // 10,

    % % LET * L
    % L1 is L * T, T2 is L1 mod 10, LC1 is L1 // 10,
    % L10 is L * E + LC1, E2 is L10 mod 10, LC10 is L10 // 10,
    % L100 is L * L + LC10, L2 is L100 mod 10, LC100 is L100 // 10,
    
    % S is S1,
    % LAdd is T1 + V1 + L2, L is LAdd mod 10, LCAdd is LAdd // 10,
    % EAdd is I1 + O1 + E2 + LCAdd, E is EAdd mod 10, ECAdd is EAdd // 10,
    % TAdd is T2 + O1 + L2 + ECAdd, T is TAdd mod 10, TCAdd is TAdd // 10,
    % I is TCAdd.    
     
     
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
    
    