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

%% To help you test your collabDistance, you may put your knowledge base below. Do not put it under the colladDistance
%% section. You may also delete your test knowledge based before submission, as we will not be marking it


%%%%% SECTION: collabDistance
%%%%% Predicate definition: collabDist(Author1, Author2, MaxDist, Authors, Articles)
collabDist(Author1, Author1, MaxDist, [Author1], [Article1]) :- MaxDist >= 0, articleAuthor(Article1, Author1).
collabDist(Author1, Author2, MaxDist, Authors, Articles) :- MaxDist >= 1, helperCollabDist(Author1, Author2, MaxDist, [], [], Authors, Articles).

helperCollabDist(Author1, Author2, MaxDist, PrevAuthors, PrevArticles, [Author1, Author2], [Article1]) :- articleAuthor(Article1, Author1), not member(Article1, PrevArticles), articleAuthor(Article1, Author2), not member(Author2, PrevAuthors), not Author1 = Author2.
helperCollabDist(Author1, Author2, MaxDist, PrevAuthors, PrevArticles, [Author1 | NextAuthors], [Article1 | NextArticles]) :- MaxDist >= 2, articleAuthor(Article1, Author1), not member(Article1, PrevArticles), articleAuthor(Article1, AuthorN), not Author1 = AuthorN, not member(AuthorN, PrevAuthors), NextMaxDist is MaxDist - 1, helperCollabDist(AuthorN, Author2, NextMaxDist, [Author1 | PrevAuthors], [Article1 | PrevArticles], NextAuthors, NextArticles).

member(X, [X | Tail]).
member(X, [Y | Tail]) :- member(X, Tail).
