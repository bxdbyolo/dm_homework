% Тест 1: Пустой граф
test(empty_graph) :-
    do_dfs([], 0, Path),
    Path == [],
    format('Test empty_graph passed! Path: ~w~n', [Path]).

% Тест 2: Граф с одной вершиной без ребер
test(single_vertex_no_edges) :-
    do_dfs([], 1, Path),
    Path == [1],
    format('Test single_vertex_no_edges passed! Path: ~w~n', [Path]).

% Тест 3: Граф с двумя несвязанными вершинами
test(two_disconnected_vertices) :-
    do_dfs([], 2, Path),
    (Path == [1, 2] ; Path == [2, 1]),
    format('Test two_disconnected_vertices passed! Path: ~w~n', [Path]).

% Тест 4: Граф с двумя связанными вершинами
test(two_connected_vertices) :-
    do_dfs([(1,2), (2,1)], 2, Path),
    (Path == [1, 2] ; Path == [2, 1]),
    format('Test two_connected_vertices passed! Path: ~w~n', [Path]).

% Тест 5: Линейный граф 1-2-3
test(linear_graph) :-
    do_dfs([(1,2), (2,3)], 3, Path),
    (Path == [1, 2, 3] ; Path == [3, 2, 1]), % возможны оба варианта
    format('Test linear_graph passed! Path: ~w~n', [Path]).

% Тест 6: Циклический граф 1-2-3-1
test(cyclic_graph) :-
    do_dfs([(1,2), (2,3), (3,1)], 3, Path),
    (Path == [1, 2, 3] ; Path == [2, 3, 1] ; Path == [3, 1, 2]),
    format('Test cyclic_graph passed! Path: ~w~n', [Path]).

% Тест 7: Граф в форме дерева
test(tree_graph) :-
    do_dfs([(1,2), (1,3), (2,4), (2,5), (3,6), (3,7)], 7, Path),
    % Проверяем что все вершины присутствуют и порядок обхода логичен
    sort(Path, Sorted),
    Sorted == [1,2,3,4,5,6,7],
    format('Test tree_graph passed! Path: ~w~n', [Path]).

% Запуск всех тестов с обработкой ошибок
run_tests :-
    findall(Test, (
        member(Test, [
            empty_graph,
            single_vertex_no_edges,
            two_disconnected_vertices,
            two_connected_vertices,
            linear_graph,
            cyclic_graph,
            tree_graph
        ]),
        (test(Test) -> true ; format('Test ~w failed!~n', [Test]), fail)
    ), _),
    format('All tests completed!~n').