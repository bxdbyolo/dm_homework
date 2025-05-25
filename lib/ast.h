#pragma once

#include <vector>

#include "token.h"
#include "nonterminal.h"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual bool equals(const ASTNode* other) const = 0;
    virtual void print(int indent = 0) const = 0;
};

class Leaf final : public ASTNode {
    Token token;

public:
    Leaf(Token t);
    bool equals(const ASTNode *other) const override;
    void print(int indent) const override;
};

class InnerNode : public ASTNode {
    NonTerminal nt;
    std::vector<std::unique_ptr<ASTNode>> children;

public:
    InnerNode(NonTerminal nt);

    template<typename... Args>
    InnerNode(const NonTerminal nt, Args&&... args) : nt(nt) {
        (children.emplace_back(std::forward<Args>(args)), ...);
    }

    void addChild(std::unique_ptr<ASTNode> child) {
        children.push_back(std::move(child));
    }

    bool equals(const ASTNode *other) const override;
    void print(int indent) const override;
};
