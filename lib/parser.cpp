#include "parser.h"

Parser::Parser(const Grammar &gr, const std::vector<Token> &tokens)
    : grammar(gr), tokens(tokens) {}

Token Parser::current() const {
    return pos < tokens.size() ? tokens[pos] : Token::EOF_TOKEN();
}

void Parser::consume() {
    if (pos < tokens.size()) pos++;
}

bool Parser::match(const TokenType type) {
    if (current().type == type) {
        consume();
        return true;
    }
    return false;
}

std::unique_ptr<ASTNode> Parser::parse() {
    auto result = parseR0();
    if (current().type != TokenType::EOF_TOKEN)
        throw std::runtime_error("Unexpected token at the end of input");
    return result;
}

std::unique_ptr<ASTNode> Parser::parseR0() {
    auto s0 = parseS0();
    auto r1 = parseR1();
    return std::make_unique<InnerNode>(R0, std::move(s0), std::move(r1));
}

std::unique_ptr<ASTNode> Parser::parseR1() {
    if (match(TokenType::CHOICE)) {
        auto s0 = parseS0();
        auto r1 = parseR1();
        return std::make_unique<InnerNode>(R1,
            std::make_unique<Leaf>(Token::CHOICE()),
            std::move(s0),
            std::move(r1));
    }
    return std::make_unique<InnerNode>(R1, std::make_unique<Leaf>(Token::EPSILON()));
}

std::unique_ptr<ASTNode> Parser::parseS0() {
    auto t = parseT();
    auto s1 = parseS1();
    return std::make_unique<InnerNode>(S0, std::move(t), std::move(s1));
}

std::unique_ptr<ASTNode> Parser::parseS1() {
    if (grammar.inFirst(S1, current().type)) {
        auto t = parseT();
        auto s1 = parseS1();
        return std::make_unique<InnerNode>(S1, std::move(t), std::move(s1));
    }

    if (grammar.inFollow(S1, current().type)) {
        return std::make_unique<InnerNode>(S1, std::make_unique<Leaf>(Token::EPSILON()));
    }
    throw std::runtime_error("Unexpected token in S1");
}

std::unique_ptr<ASTNode> Parser::parseT() {
    auto a = parseA();
    auto c = parseC();
    return std::make_unique<InnerNode>(T, std::move(a), std::move(c));
}

std::unique_ptr<ASTNode> Parser::parseA() {
    if (match(TokenType::CHAR)) {
        return std::make_unique<InnerNode>(A,
            std::make_unique<Leaf>(tokens[pos-1]));
    }

    if (match(TokenType::LPAREN)) {
        auto r0 = parseR0();
        if (!match(TokenType::RPAREN)) {
            throw std::runtime_error("Expected ')'");
        }
        return std::make_unique<InnerNode>(A,
            std::make_unique<Leaf>(Token::LPAREN()),
            std::move(r0),
            std::make_unique<Leaf>(Token::RPAREN()));
    }

    throw std::runtime_error("Unexpected token in A");
}

std::unique_ptr<ASTNode> Parser::parseC() {
    if (match(TokenType::KLEENE)) {
        auto c = parseC();
        return std::make_unique<InnerNode>(C,
            std::make_unique<Leaf>(Token::KLEENE()),
            std::move(c));
    }

    if (match(TokenType::PLUS)) {
        auto c = parseC();
        return std::make_unique<InnerNode>(C,
            std::make_unique<Leaf>(Token::PLUS()),
            std::move(c));
    }

    if (match(TokenType::QUESTION)) {
        auto c = parseC();
        return std::make_unique<InnerNode>(C,
            std::make_unique<Leaf>(Token::QUESTION()),
            std::move(c));
    }

    return std::make_unique<InnerNode>(C, std::make_unique<Leaf>(Token::EPSILON()));
}
