% Read input predicate
read_input(File, N, K, C) :- open(File, read, Stream), read_line(Stream, [N, K]), read_line(Stream, C).
read_line(Stream, L) :- read_line_to_codes(Stream, Line), atom_codes(Atom, Line), atomic_list_concat(Atoms, ' ', Atom), maplist(atom_number, Atoms, L).

% A predicate that initializes a list of N elements to the value of X
build(_, 0, []). 
build(X, N, [X|L]) :- N > 0, N1 is N - 1, build(X, N1, L), !.

% A predicate update_inc/3 that increases respective counters of colors - https://bit.ly/2yKGpMf
replace([_|T], 0, X, [X|T]).
replace([H|T], I, V, [H|N]) :- 
    I > 0, I1 is I-1, replace(T, I1, V, N).
update_inc(List, Index, NewList) :- 
    replace(List, Index, El, NewList), nth0(Index, List, Elem), El is Elem+1, !.

% A predicate update_inc/3 that decreases respective counters of colors
update_dec(List, Index, NewList) :- 
    replace(List, Index, El, NewList), nth0(Index, List, Elem), El is Elem-1, !.

% A predicate all_colors/1 that checks colors counter to decide whethers all colors are met 
check([]).
check([H|L]) :- \+H = 0, check(L).
all_colors([H|L]) :- H = 0, check(L).

% A predicate locate_tail/5 that locates the ending pointer of a valid sequence
locate_tail(_, Counters, EndingP, GlobalIteration, FinalCounters, FinalP) :- % Check all counter list for only the first iteration
    GlobalIteration = 0, all_colors(Counters), FinalCounters = Counters, FinalP is EndingP-1, !.
locate_tail(_, Counters, EndingP, GlobalIteration, FinalCounters, FinalP) :- % Check only the respective counter cell for the rest of iterations
    \+GlobalIteration = 0, all_colors(Counters), FinalCounters = Counters, FinalP is EndingP-1, !.
locate_tail(List, Counters, EndingP, _, FinalCounters, FinalP) :- 
    nth0(EndingP, List, Index), update_inc(Counters, Index, NewCounters),
    NewEndingP is EndingP+1, locate_tail(List, NewCounters, NewEndingP, 1, FinalCounters, FinalP).

% A predicate locate_head/5 that locates the best possible starting pointer for a potential valid sequence
locate_head(List, Counters, StartingP, Iteration, FinalCounters, FinalP) :- 
    ( \+Iteration = 0 ->
        nth0(StartingP, List, Element), nth0(Element, Counters, El), El = 1, FinalCounters = Counters, FinalP is StartingP, !
    ;
        false
    ).
locate_head(List, Counters, StartingP, Iteration, FinalCounters, FinalP) :- 
    nth0(StartingP, List, Index), update_dec(Counters, Index, NewCounters), NewStartingP is StartingP+1, 
    NewIteration is Iteration+1, locate_head(List, NewCounters, NewStartingP, NewIteration, FinalCounters, FinalP).
