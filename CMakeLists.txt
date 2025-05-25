cmake_minimum_required(VERSION 3.10)
project(RegexParser CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_executable(regex
        main.cpp
        lib/lexer.h
        lib/token.h
        lib/lexer.cpp
        lib/grammar.h
        lib/nonterminal.h
        lib/grammar.cpp
        lib/parser.cpp
        lib/parser.h
        lib/ast.cpp
        lib/ast.h)

target_link_libraries(regex PRIVATE regex_lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
