#pragma once

#include <vector>
#include <list>
#include <string>

#include "Lexer.h"
#include "Token.h"
#include "TokenType.h"
#include "Node.h"
#include "NodePrinter.h"


class Parser {
public:
    Parser(std::vector<Token> tokens);
    ExprStmtNode *root;

    std::list<DeclNode*> parse();

private:
    std::vector<Token> tokens_;
    unsigned int current_idx = 0;

    bool isAtEnd();

    Token consume();
    TokenType peek();
    bool match(TokenType t);

    void parseToken();

    //std::list<StmtNode*> parse();
    DeclNode* parse_decl_();
    StmtNode* parse_stmt_();
    ExprStmtNode* parse_expr_stmt_();
    ForStmtNode* parse_for_stmt_();
    IfStmtNode* parse_if_stmt_();
    PrintStmtNode* parse_print_stmt_();
    ReturnStmtNode* parse_return_stmt_();
    WhileStmtNode* parse_while_stmt_();
    BlockNode* parse_block_();
    LiteralNode* parse_literal_();
    GroupingNode* parse_grouping_();
    UnaryNode* parse_unary_(TokenType t);
    BinaryNode* parse_binary_(ExprStmtNode *current);
    VarDeclNode* parse_var_decl_();
    FuncDeclNode* parse_func_decl_();
    ClassDeclNode* parse_class_decl_();
    ParametersNode* parse_params_();
    void parse_operator_();
    NumberNode* parse_number_(int num);
    StringNode* parse_string(std::string str);
    IdentifierNode* parse_identifier(std::string str);
};
