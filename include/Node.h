#pragma once

#include "Token.h"
#include "TokenType.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <string>
#include <vector>

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

class BlockNode {
public:
    BlockNode() {}
    virtual Value *codegen();
    std::vector<StmtNode*> statements;
};

class IdentifierNode : public ExprStmtNode {
public:
    IdentifierNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class ParametersNode {
public:
    ParametersNode() {}
    virtual Value *codegen();

    std::vector<IdentifierNode*> identifiers;
};

class IfStmtNode : public StmtNode {
public:
    IfStmtNode() {}
    virtual Value *codegen() override;

    ExprStmtNode *if_expr;
    ExprStmtNode *else_expr;
    BlockNode    *if_block;
    BlockNode    *else_block;
};

class PrintStmtNode : public StmtNode {
public:
    PrintStmtNode(ExprStmtNode *expr) :
        exprStmt(expr) {}
    virtual Value *codegen() override;

    ExprStmtNode *exprStmt;
};

class ReturnStmtNode : public StmtNode {
public:
    ReturnStmtNode() {}
    virtual Value *codegen() override;

    // Grammar
    // return ;
    // return ExprStmt ;

    // this flag indicates if return statement returns any expression or not
    bool return_void;
    ExprStmtNode *ret_expr;
};

class WhileStmtNode : public StmtNode {
public:
    WhileStmtNode() {}
    virtual Value *codegen();

    ExprStmtNode *conditional_expr;
    BlockNode    *loop_block;
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

// identifierNode below this line -

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

class FuncDeclNode : public DeclNode {
public:
    FuncDeclNode() {}
    virtual Value *codegen();

    bool empty_param;
    IdentifierNode *func_iden;
    ParametersNode *params;
    BlockNode      *func_block;
};

class ClassDeclNode : public DeclNode {
public:
    ClassDeclNode() {}
    virtual Value *codegen();

    // TODO: define child nodes
};

class ForStmtNode : public StmtNode {
public:
    ForStmtNode() {}
    virtual Value *codegen() override;

    VarDeclNode  *init;
    ExprStmtNode *condition;
    ExprStmtNode *update;
    BlockNode    *loop_block;
};
