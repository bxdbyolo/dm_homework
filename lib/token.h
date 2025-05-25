#pragma once

enum class TokenType {
    CHAR, // a-z
    CHOICE, // |
    KLEENE, // *
    PLUS, // +
    QUESTION, // ?
    LPAREN, // (
    RPAREN, // )
    EPSILON, // ε
    EOF_TOKEN // конец ввода
};

struct Token {
    TokenType type;
    char value;

    static inline Token AT(const char c) { return {TokenType::CHAR, c}; }
    static inline Token CHOICE() { return {TokenType::CHOICE, 0}; }
    static inline Token KLEENE() { return {TokenType::KLEENE, 0}; }
    static inline Token PLUS() { return {TokenType::PLUS, 0}; }
    static inline Token QUESTION() { return {TokenType::QUESTION, 0}; }
    static inline Token LPAREN() { return {TokenType::LPAREN, 0}; }
    static inline Token RPAREN() { return {TokenType::RPAREN, 0}; }
    static inline Token EPSILON() { return {TokenType::EPSILON, 0}; }
    static inline Token EOF_TOKEN() { return {TokenType::EOF_TOKEN, 0}; }

};
