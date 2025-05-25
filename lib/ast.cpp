#include "ast.h"
#include <iostream>

Leaf::Leaf(const Token t) : token(t) {}

bool Leaf::equals(const ASTNode *other) const {
    const auto leaf = dynamic_cast<const Leaf*>(other);
    return leaf && token.type == leaf->token.type && token.value == leaf->token.value;
}

void Leaf::print(const int indent) const {
    std::cout << std::string(indent, ' ') << "Leaf: ";
    switch (token.type) {
        case TokenType::CHAR: std::cout << token.value; break;
        case TokenType::CHOICE: std::cout << "|"; break;
        case TokenType::KLEENE: std::cout << "*"; break;
        case TokenType::LPAREN: std::cout << "("; break;
        case TokenType::RPAREN: std::cout << ")"; break;
        case TokenType::EPSILON: std::cout << "ε"; break;
        default: std::cout << "?"; break;
    }
    std::cout << std::endl;
}


InnerNode::InnerNode(const NonTerminal nt) : nt(nt) {}

bool InnerNode::equals(const ASTNode *other) const {
    const auto node = dynamic_cast<const InnerNode*>(other);
    if (!node || nt != node->nt || children.size() != node->children.size())
        return false;

    for (size_t i = 0; i < children.size(); ++i) {
        if (!children[i]->equals(node->children[i].get()))
            return false;
    }
    return true;
}

void InnerNode::print(int indent) const {
    std::cout << std::string(indent, ' ') << "Node: ";
    switch (nt) {
        case R0: std::cout << "R0"; break;
        case R1: std::cout << "R1"; break;
        case S0: std::cout << "S0"; break;
        case S1: std::cout << "S1"; break;
        case T: std::cout << "T"; break;
        case A: std::cout << "A"; break;
        case C: std::cout << "C"; break;
    }
    std::cout << std::endl;

    for (auto& child : children) child->print(indent + 2);
}

