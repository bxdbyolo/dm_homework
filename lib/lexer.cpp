#include "lexer.h"

Lexer::Lexer(const std::string &str) : input(str) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < input.size()) {
        const char c = input[pos++];
        if (c >= 'a' && c <= 'z') {
            tokens.push_back(Token::AT(c));
        } else switch(c) {
            case '|': tokens.push_back(Token::CHOICE()); break;
            case '*': tokens.push_back(Token::KLEENE()); break;
            case '+': tokens.push_back(Token::PLUS()); break;
            case '?': tokens.push_back(Token::QUESTION()); break;
            case '(': tokens.push_back(Token::LPAREN()); break;
            case ')': tokens.push_back(Token::RPAREN()); break;
            default: throw std::runtime_error("Invalid character: " + std::string(1, c));
        }
    }
    tokens.push_back(Token::EOF_TOKEN());
    return tokens;
}

