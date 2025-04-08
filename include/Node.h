#pragma once

#include "Token.h"
#include "TokenType.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <string>

using namespace llvm;

class DeclNode {
public:
    virtual Value *codegen() = 0;
};

/**class VarDeclNode : public DeclNode {
public:
    VarDeclNode(IdentifierNode *iden, ExprStmtNode *expr) :
        iden(iden),
        expr(expr) {}

    IdentifierNode *iden;
    ExprStmtNode *expr;
};**/

class StmtNode : public DeclNode {
public:
    StmtNode() {}
    virtual Value *codegen() = 0;
    virtual ~StmtNode() = default;
};

class ExprStmtNode : public StmtNode {
public:
    ExprStmtNode() {}
    virtual Value *codegen() override;
    ExprStmtNode *exprStmt;
};

class PrintStmtNode : public StmtNode {
public:
    PrintStmtNode(ExprStmtNode *expr) :
        exprStmt(expr) {}
    virtual Value *codegen() override;
    ExprStmtNode *exprStmt;
};

class NumberNode : public ExprStmtNode {
public:
    NumberNode(int value) :
        value_(value) {}
    Value *codegen() override;
    int value_;
};

class StringNode : public ExprStmtNode {
public:
    StringNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class LiteralNode : public ExprStmtNode {
public:
    LiteralNode(ExprStmtNode *node) :
        node(node) {}

    Value *codegen() override;
    ExprStmtNode *node;
};

class IdentifierNode : public ExprStmtNode {
public:
    IdentifierNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class UnaryNode : public ExprStmtNode {
public:
    UnaryNode(TokenType symbol, ExprStmtNode* expr) :
        symbol_(symbol), expr_(expr) {}

    Value *codegen() override;
    TokenType symbol_;
    ExprStmtNode *expr_;
};

class BinaryNode : public ExprStmtNode {
public:
    BinaryNode(ExprStmtNode* left, ExprStmtNode* right, TokenType op) :
        left_(left), right_(right), op_(op) {}

    Value *codegen() override;
    ExprStmtNode *left_;
    ExprStmtNode *right_;
    TokenType op_;
};

class GroupingNode : public ExprStmtNode {
public:
    GroupingNode(ExprStmtNode *expr) :
        expr_(expr) {}

    Value *codegen() override;
    ExprStmtNode *expr_;
};

class VarDeclNode : public DeclNode {
public:
    VarDeclNode(IdentifierNode *iden, ExprStmtNode *expr) :
        iden(iden),
        expr(expr) {}
    virtual Value *codegen();
    IdentifierNode *iden;
    ExprStmtNode *expr;
};
