#pragma once

#include <unordered_map>
#include <unordered_set>

#include "token.h"
#include "nonterminal.h"

class Grammar {
    std::unordered_map<NonTerminal, std::unordered_set<TokenType>> first;
    std::unordered_map<NonTerminal, std::unordered_set<TokenType>> follow;

public:
    Grammar();
    bool inFirst(NonTerminal nt, TokenType t) const;
    bool inFollow(NonTerminal nt, TokenType t) const;
};
