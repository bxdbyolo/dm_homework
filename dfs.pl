do_dfs(Graph, N, Path) :-
    length(Visited, N),
    maplist(=(false), Visited),
    do_dfs_helper(1, N, Graph, Visited, [], RevPath),
    reverse(RevPath, Path). % Разворачиваем путь для правильного порядка

% Все вершины обработаны
do_dfs_helper(Current, N, _, _, Path, Path) :- Current > N, !.

do_dfs_helper(Current, N, Graph, Visited, CurrentPath, Path) :-
    nth1(Current, Visited, VisitedStatus),
    (VisitedStatus == false ->
        dfs(Current, Graph, Visited, NewVisited, CurrentPath, NewPath), 
        Next is Current + 1,
        do_dfs_helper(Next, N, Graph, NewVisited, NewPath, Path)
    ;
        Next is Current + 1,
        do_dfs_helper(Next, N, Graph, Visited, CurrentPath, Path)
    ).

dfs(U, Graph, Visited, NewVisited, Path, NewPath) :-
    update_visited(U, Visited, TempVisited),
    findall(V, member((U, V), Graph), Neighbors),
    process_neighbors(Neighbors, Graph, TempVisited, NewVisited, [U|Path], NewPath).

% Обновление списка посещённых вершин
update_visited(1, [_|T], [true|T]) :- !.
update_visited(U, [H|T], [H|NewT]) :-
    U > 1,
    U1 is U - 1,
    update_visited(U1, T, NewT).

% Обработка списка соседей
process_neighbors([], _, Visited, Visited, Path, Path).
process_neighbors([V|Rest], Graph, Visited, NewVisited, Path, FinalPath) :-
    nth1(V, Visited, VisitedStatus),
    (VisitedStatus == false ->
        dfs(V, Graph, Visited, AfterVisit, Path, IntermediatePath),
        process_neighbors(Rest, Graph, AfterVisit, NewVisited, IntermediatePath, FinalPath)
    ;
        process_neighbors(Rest, Graph, Visited, NewVisited, Path, FinalPath)
    ).
    