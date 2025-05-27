add_library(regex_lib STATIC
        token.h
        nonterminal.h
        ast.h
        ast.cpp
        lexer.h
        lexer.cpp
        grammar.h
        grammar.cpp
        parser.h
        parser.cpp
)

target_include_directories(regex_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
