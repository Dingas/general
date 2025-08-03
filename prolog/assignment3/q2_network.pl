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

%%%%% SECTION: networkSolve
%%%%% Below, you should define rules for the predicate "solve", which takes in your list of
%%%%% variables and finds an assignment for each variable which solves the problem.
%%%%%
%%%%% You should also define rules for the predicate "solve_and_print" which calls your
%%%%% solve predicate and prints out the results in an easy to read, human readable format.
%%%%% The predicate "solve_and_print" should take in no arguments
% domain of systems
sys(1). sys(2). sys(3). sys(4). sys(5). sys(6).

% direct links between systems
directLink(6, [5]).
directLink(5, [6, 3]).
directLink(3, [5, 4, 2]).
directLink(4, [3]).
directLink(2, [3, 1]).
directLink(1, [2, out]).
directLink(out, [1]).

solve([B, F, N, P, S, U, C, L, M, A, D, J, E, K, O, T, W, Z]) :-
% constraint 1
sys(L), sys(O), not L = O, trip(L, O, Con1), sys(P), member(P, Con1), not member(P, [L, O]),

% constraint 5, order is to reduce backtracking of tests independent of L
sys(C), not C = L, sys(M), not member(M, [L, C]), sys(T), not T = O, member(T, [C, L, M]), sys(J), not member(J, [L, C, M]), trip(J, T, Con5), sys(U), not U = P, member(U, Con5), not member(U, [J, T]),

% constraint 6, order is to reduce backtracking of tests independent of L, C, and M
sys(B), not member(B, [P, U]), member(B, [C, L, M]),

% constraint 2, order is to reduce backtracking of tests independent of M
sys(W), not member(W, [O, T]), directLink(M, Mdl), member(W, Mdl), sys(N), not member(N, [P, U, B]), member(N, [M, W]),

% constraint 3, order is to reduce backtracking of tests independent of J
sys(A), not member(A, [L, C, M, J]), trip(A, J, Con3), sys(E), not member(E, [O, T, W]), member(E, Con3), not member(E, [A, J]),

% constraint 8, order is to reduce backtracking of tests independent of C and N
sys(Z), not member(Z, [O, T, W, E]), directLink(Z, Zdl), member(C, Zdl), member(N, Zdl), onlyMembers([C, N, out], Zdl),

% constraint 4
sys(D), not member(D, [L, C, M, J, A]), directLink(D, Ddl), sys(S), not member(S, [P, U, B, N]), member(S, Ddl), onlyMembers([S, out], Ddl),

% constraint 7
sys(K), not member(K, [O, T, W, E, Z]), trip(K, out, Con7), sys(F), not member(F, [P, U, B, N, S]), member(F, Con7), not F = K.

solve_and_print :- solve([B, F, N, P, S, U, C, L, M, A, D, J, E, K, O, T, W, Z]),
write('Address         System'), nl,
write('______________________'), nl,
write('bananas.com     '), write(B), nl,
write('firstbank.com   '), write(F), nl,
write('netvue.com      '), write(N), nl,
write('pricenet.com    '), write(P), nl,
write('sysworld.com    '), write(S), nl,
write('univmoose.edu   '), write(U), nl,
write('______________________'), nl,
write('First Name      System'), nl,
write('______________________'), nl,
write('Catarina        '), write(C), nl,
write('Lizzie          '), write(L), nl,
write('Mona            '), write(M), nl,
write('Anthony         '), write(A), nl,
write('Daniel          '), write(D), nl,
write('Jaime           '), write(J), nl,
write('______________________'), nl,
write('Last Name       System'), nl,
write('______________________'), nl,
write('Elby            '), write(E), nl,
write('Kim             '), write(K), nl,
write('Osborne         '), write(O), nl,
write('Tsuji           '), write(T), nl,
write('Wolverton       '), write(W), nl,
write('Zickerman       '), write(Z), nl.



%%%%% SECTION: trip
%%%%% Below, you should define rules for the predicate "trip", which takes in 
%%%%% two computer systems and returns the list of locations in between them.
%%%%% The signature of this predicate is trip(From,To,Path)
% base cases
trip(X, X, [X]).
trip(Origin, Destination, [Origin, Destination]) :- directLink(Origin, DL), member(Destination, DL).

% recursive case
trip(Origin, Destination, Path) :- helperTrip(Origin, Destination, [Origin, Destination], Path).
helperTrip(Origin, Destination, PrevPath, [Origin, Destination]) :- directLink(Origin, DL), member(Destination, DL).
helperTrip(Origin, Destination, PrevPath, [Origin | Rest]) :- directLink(Origin, DL), member(Next, DL), not member(Next, PrevPath), helperTrip(Next, Destination, [Origin | PrevPath], Rest).

member(X, [X | Tail]).
member(X, [Y | Tail]) :- member(X, Tail).

% helper to check if a list contains only the members of another list
onlyMembers(X, []).
onlyMembers(X, [Head | Tail]) :- member(Head, X), onlyMembers(X, Tail).
