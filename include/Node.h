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

    std::shared_ptr<ExprStmtNode> exprStmt;
};

class BlockNode {
public:
    BlockNode() {}
    virtual Value *codegen();
    std::vector<std::shared_ptr<DeclNode>> declarations;
};

class IdentifierNode : public ExprStmtNode {
public:
    IdentifierNode(std::string value) :
        value_(value) {}

    Value *codegen() override;
    std::string value_;
};

class AssignStmtNode : public StmtNode {
public:
    AssignStmtNode() {}
    virtual Value *codegen() override;

    std::shared_ptr<IdentifierNode> iden;
    std::shared_ptr<ExprStmtNode> exprStmt;
};

class ParametersNode {
public:
    ParametersNode() {}
    virtual Value *codegen();

    std::vector<std::shared_ptr<IdentifierNode>> identifiers;
};

class IfStmtNode : public StmtNode {
public:
    IfStmtNode() {}
    virtual Value *codegen() override;

    std::shared_ptr<ExprStmtNode> if_expr;
    std::shared_ptr<ExprStmtNode> else_expr;
    std::shared_ptr<BlockNode>    if_block;
    std::shared_ptr<BlockNode>    else_block;
};

class PrintStmtNode : public StmtNode {
public:
    PrintStmtNode(std::shared_ptr<ExprStmtNode> expr) :
        exprStmt(expr) {}
    virtual Value *codegen() override;

    std::shared_ptr<ExprStmtNode> exprStmt;
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
    std::shared_ptr<ExprStmtNode> ret_expr;
};

class WhileStmtNode : public StmtNode {
public:
    WhileStmtNode() {}
    virtual Value *codegen();

    std::shared_ptr<ExprStmtNode> conditional_expr;
    std::shared_ptr<BlockNode>    loop_block;
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
    LiteralNode(std::shared_ptr<ExprStmtNode> node) :
        node(node) {}

    Value *codegen() override;
    std::shared_ptr<ExprStmtNode> node;
};

// identifierNode below this line -

class UnaryNode : public ExprStmtNode {
public:
    UnaryNode(TokenType symbol, std::shared_ptr<ExprStmtNode> expr) :
        symbol_(symbol), expr_(expr) {}

    Value *codegen() override;
    TokenType symbol_;
    std::shared_ptr<ExprStmtNode> expr_;
};

class BinaryNode : public ExprStmtNode {
public:
    BinaryNode(std::shared_ptr<ExprStmtNode> left, std::shared_ptr<ExprStmtNode> right, TokenType op) :
        left_(left), right_(right), op_(op) {}

    Value *codegen() override;
    std::shared_ptr<ExprStmtNode> left_;
    std::shared_ptr<ExprStmtNode> right_;
    TokenType op_;
};

class GroupingNode : public ExprStmtNode {
public:
    GroupingNode(std::shared_ptr<ExprStmtNode> expr) :
        expr_(expr) {}

    Value *codegen() override;
    std::shared_ptr<ExprStmtNode> expr_;
};

class VarDeclNode : public DeclNode {
public:
    VarDeclNode(std::shared_ptr<IdentifierNode> iden, std::shared_ptr<ExprStmtNode> expr) :
        iden(iden),
        expr(expr) {}
    virtual Value *codegen();
    std::shared_ptr<IdentifierNode> iden;
    std::shared_ptr<ExprStmtNode> expr;
};

class FuncDeclNode : public DeclNode {
public:
    FuncDeclNode() {}
    virtual Value *codegen();

    bool empty_param;
    std::shared_ptr<IdentifierNode> func_iden;
    std::shared_ptr<ParametersNode> params;
    std::shared_ptr<BlockNode>      func_block;
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

    std::shared_ptr<VarDeclNode>  init;
    std::shared_ptr<ExprStmtNode> condition;
    std::shared_ptr<ExprStmtNode> update;
    std::shared_ptr<BlockNode>    loop_block;
};
