#pragma once

#include <iostream>
#include "token.h"

class Lexer {
    std::string input;
    size_t pos{0};

public:
    Lexer(const std::string& str);
    std::vector<Token> tokenize();
};
