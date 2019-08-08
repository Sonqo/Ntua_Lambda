% A predicate that initializes a list of N elements to the value of X
build(_, 0, []). 
build(X, N, [X|L]) :- N > 0, N1 is N - 1, build(X, N1, L).

% A predicate update_inc/3 that increases respective counters of colors - https://bit.ly/2yKGpMf
replace([_|T], 0, X, [X|T]).
replace([H|T], I, V, [H|N]):- I > 0, I1 is I-1, replace(T, I1, V, N).
update_inc(List, Index, NewList) :- replace(List, Index, El, NewList), nth0(Index, List, Elem), El is Elem+1, !.

% A predicate update_inc/3 that decreases respective counters of colors
update_dec(List, Index, NewList) :- replace(List, Index, El, NewList), nth0(Index, List, Elem), El is Elem-1, !.

% A predicate all_colors/1 that checks colors counter to decide whethers all colors are met 
check([]).
check([H|L]) :- \+H = 0, check(L).
all_colors([H|L]) :- H = 0, check(L).

% A predicate locate_seq/3 that returns the counter list of the first completed sequence of colors
% locate_seq(_, Counters, NewCounters, _, _) :- all_colors(Counters), NewCounters = Counters, !.
% locate_seq([H|L], Counters, FinalCounters, StartingP, FinalP) :- update_inc([H|L], Counters, NewCounters), locate_seq(L, NewCounters, FinalCounters).
