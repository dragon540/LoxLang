#pragma once

#include "Token.h"
#include "TokenType.h"

#include <string>

class ASTNode {
public:
    ASTNode();
};

class NumberNode : public ASTNode {
public:
    NumberNode(int value) :
        value_(value) {}

    int value_;
};

class StringNode : public ASTNode {
public:
    StringNode(std::string value) :
        value_(value) {}

    std::string value_;
};

class Expr : public ASTNode {
public:
    Expr();
};

class Literal : public Expr {
public:
    Token *val_;
    Literal();
};

class Unary : public Expr {
public:
    Unary(TokenType symbol, Expr* expr) :
        symbol_(symbol), expr_(expr) {}

    TokenType symbol_;
    Expr *expr_;
};

class Binary : public Expr {
public:
    /**Binary(Expr* left, Expr* right, TokenType op_) :
        left_(left), right_(right), op_(op) {}
**/
    Expr *left_;
    Expr *right_;
    TokenType op_;
};

class Grouping : public Expr {
public:
    Grouping(Expr *expr) :
        expr_(expr) {}

    Expr *expr_;
};
