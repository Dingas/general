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

%%%%% SECTION: articleAuthor
% Put your atomic statements for the articleAuthor predicate in this section

articleAuthor('linear_algebra', 'james').
articleAuthor('linear_algebra', 'alex').
articleAuthor('intro_to_ai', 'jennifer').
articleAuthor('intro_to_ai', 'peter').
articleAuthor('intro_to_ai', 'mark').
articleAuthor('intro_to_ai', 'dave').
articleAuthor('topology', 'paul').
articleAuthor('topology', 'alex').
articleAuthor('topology', 'michael').
articleAuthor('cybersecurity', 'eve').
articleAuthor('cybersecurity', 'alex').
articleAuthor('prolog_basics', 'alice').
articleAuthor('prolog_basics', 'frank').
articleAuthor('prolog_basics', 'mark').
articleAuthor('advanced_calculus', 'george').
articleAuthor('advanced_calculus', 'helen').
articleAuthor('advanced_calculus', 'jennifer').
articleAuthor('networking_principles', 'josh').

%%%%% SECTION: articleTopic
% Put your atomic statements for the articleTopic predicate in this section

articleTopic('linear_algebra', 'mathematics').
articleTopic('intro_to_ai', 'ai').
articleTopic('cybersecurity', 'cybersecurity').
articleTopic('prolog_basics', 'programming').
articleTopic('advanced_calculus', 'mathematics').
articleTopic('networking_principles','information_technology').

%%%%% SECTION: collabDist
% Put your rules for collabDist in this section

% Base case when A1 == A2, check if they have authored an article (MaxDist = 0) to themselves.

collabDist(Author, Author, _) :-
    articleAuthor(_, Author).

% Base case where there is a direct collaboration path between authors (MaxDist > 0).

collabDist(Author1, Author2, MaxDist) :- 
    MaxDist > 0,
    articleAuthor(Article, Author1),
    articleAuthor(Article, Author2),
    Author1 \= Author2.
   
% Recursive Case, incrementally step through potential collaboration paths by decrementing MaxDist.
% recursively calling collabDist (MaxDist > 1).

collabDist(Author1, Author2, MaxDist) :-
	MaxDist > 1,
	articleAuthor(Article, Author1),
	articleAuthor(Article, AuthorX),
	Author1 \= AuthorX, 
	NewMaxDist is MaxDist - 1,
	collabDist(AuthorX, Author2, NewMaxDist).


%%%% SECTION: collabDistWithAI
% Put your rules for collabDistWithAI in this section

% Base case with none.

collabDistWithAI(Author, Author, _, none) :-
	articleAuthor(Article, Author),
	\+(articleTopic(Article, 'ai').

% Base case with at least one.

collabDistWithAI(Author, Author, _, at_least_one) :-
	articleAuthor(Article, Author),
	articleTopic(Article, 'ai').

% Check for direct collaboration, none case.

collabDistWithAI(Author1, Author2, MaxDist, none) :- 
	MaxDist > 0, 
	articleAuthor(Article, Author1),
	articleAuthor(Article, Author2),
	\+ articleTopic(Article, 'ai'),
	Author1 \= Author2.

% Recursive check with none (MaxDist > 1).

collabDistWithAI(Author1, Author2, MaxDist, none) :-
	MaxDist > 1,
	articleAuthor(Article, Author1),
	\+ articleTopic(Article, 'ai'),
	articleAuthor(Article, AuthorX),
	Author1 \= AuthorX,
	NewMaxDist is MaxDist -1,
	collabDistWithAI(AuthorX, Author2, NewMaxDist, none).
	
% Check for direct collaboration, at_least_one case.
	
collabDistWithAI(Author1, Author2, MaxDist, at_least_one) :-
	MaxDist > 0,
	articleAuthor(Article, Author1),
	articleAuthor(Article, Author2),
	articleTopic(Article, 'ai'),
	Author1 \= Author2.
	
% Recursive check with at least one.

collabDistWithAI(Author1, Author2, MaxDist, at_least_one) :-
	MaxDist > 1,
	articleAuthor(Article, Author1),
	articleAuthor(Article, AuthorX),
	Author1 \= AuthorX,
	articleTopic(Article, 'ai').
	
collabDistWithAI(Author1, Author2, MaxDist, at_least_one) :-
	MaxDist > 1,
	articleAuthor(Article, Author1),
	articleAuthor(Article, AuthorX),
	Author1 \= AuthorX,
	NewMaxDist is MaxDist -1,
	collabDistWithAI(AuthorX, Author2, NewMaxDist, at_least_one).
	














