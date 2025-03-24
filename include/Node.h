#pragma once

#include "Token.h"
#include "TokenType.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <string>

using namespace llvm;

class ExprNode {
public:
    ExprNode() {}
    virtual ~ExprNode() = default;
    virtual Value *codegen() = 0;
};

class NumberNode : public ExprNode {
public:
    NumberNode(int value) :
        value_(value) {}
    Value *codegen() override;
    int value_;
};

class StringNode : public ExprNode {
public:
    StringNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class LiteralNode : public ExprNode {
public:
    LiteralNode(ExprNode *node) :
        node(node) {}

    Value *codegen() override;
    ExprNode *node;
};

class IdentifierNode : public ExprNode {
public:
    IdentifierNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class UnaryNode : public ExprNode {
public:
    UnaryNode(TokenType symbol, ExprNode* expr) :
        symbol_(symbol), expr_(expr) {}

    Value *codegen() override;
    TokenType symbol_;
    ExprNode *expr_;
};

class BinaryNode : public ExprNode {
public:
    BinaryNode(ExprNode* left, ExprNode* right, TokenType op) :
        left_(left), right_(right), op_(op) {}

    Value *codegen() override;
    ExprNode *left_;
    ExprNode *right_;
    TokenType op_;
};

class GroupingNode : public ExprNode {
public:
    GroupingNode(ExprNode *expr) :
        expr_(expr) {}

    Value *codegen() override;
    ExprNode *expr_;
};
