% Names: Chris Breniser, Nick Giles, Ryan Howerton, Quinn Thompson

% Exercise 1
when(275, 10).
when(261, 12).
when(381, 11).
when(398, 12).
when(399, 12).
where(275, owen102).
where(261, dear118).
where(381, cov216).
where(398, dear118).
where(399, cov216).
enroll(mary, 275).
enroll(john, 275).
enroll(mary, 261).
enroll(john, 381).
enroll(jim, 399).

% Exercise 1.a
schedule(S, P, T) :- enroll(S, C), where(C, P), when(C, T).

% Exercise 1.b
usage(P, T) :- where(C, P), when(C, T).

% Exercise 1.c
conflict(X, Y) :- where(X, A), when(X, B), where(Y, A), when(Y, B), X\=Y.

% Exercise 1.d
meet(X, Y) :- schedule(X, P, T), schedule(Y, P, T), X\=Y.
meet(X, Y) :- schedule(X, P, T), schedule(Y, P, R), R=:=T+1, X\=Y.
meet(X, Y) :- schedule(X, P, T), schedule(Y, P, R), R=:=T-1, X\=Y.

% Exercise 2.a
rdup([], []).
rdup([X], [X]).
rdup([X, X|L], M) :- rdup([X|L], M).
rdup([X, Y|L], [X|M]) :- rdup([Y|L], M), X\=Y.

% Exercise 2.b
flat([], []).
flat([X|L], F) :- append(X, L, Q), flat(Q, F).
flat([X|L], [X|F]) :- \+ is_list(X), flat(L, F).

% Exercise 2.c helper function
subtract_one([], []).
subtract_one([X|A], [Y|B]) :- Y is X-1, subtract_one(A, B).

% Exercise 2.c
project(_, [], []).
project([], _, []).
project([X|A], [Y|B], [Y|L]) :- X=:=1, subtract_one(A, Z), project(Z, B, L).
project([X|A], [_|B], L) :- subtract_one([X|A], Z), project(Z, B, L).