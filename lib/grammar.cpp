#pragma once

#include "grammar.h"

Grammar::Grammar() {
    first[R0] = {TokenType::CHAR, TokenType::LPAREN};
    first[R1] = {TokenType::CHOICE, TokenType::EPSILON};
    first[S0] = {TokenType::CHAR, TokenType::LPAREN};
    first[S1] = {TokenType::CHAR, TokenType::LPAREN, TokenType::EPSILON};
    first[T] = {TokenType::CHAR, TokenType::LPAREN};
    first[A] = {TokenType::CHAR, TokenType::LPAREN};
    first[C] = {TokenType::KLEENE, TokenType::PLUS, TokenType::QUESTION, TokenType::EPSILON};

    follow[R0] = {TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[R1] = {TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[S0] = {TokenType::CHOICE, TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[S1] = {TokenType::CHOICE, TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[T] = {TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[A] = {TokenType::KLEENE, TokenType::PLUS, TokenType::QUESTION,
                TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
    follow[C] = {TokenType::CHAR, TokenType::LPAREN, TokenType::CHOICE,
                TokenType::EOF_TOKEN, TokenType::RPAREN};
}

bool Grammar::inFirst(const NonTerminal nt, const TokenType t) const {
    return first.at(nt).count(t);
}

bool Grammar::inFollow(const NonTerminal nt, const TokenType t) const {
    return follow.at(nt).count(t);
}

