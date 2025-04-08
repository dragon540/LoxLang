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

    std::list<StmtNode*> parse();

private:
    std::vector<Token> tokens_;
    unsigned int current_idx = 0;

    bool isAtEnd();

    Token consume();
    TokenType peek();
    bool match(TokenType t);

    void parseToken();

    //std::list<StmtNode*> parse();
    StmtNode* parse_stmt_();
    ExprStmtNode* parse_expr_stmt_();
    PrintStmtNode* parse_print_stmt_();
    UnaryNode* parse_unary_();
    BinaryNode* parse_binary_();
    GroupingNode* parse_grouping_();
    void parse_operator_();
    NumberNode* parse_number_(int num);
    StringNode* parse_string(std::string str);
    IdentifierNode* parse_identifier(std::string str);
    LiteralNode* parse_literal(ExprStmtNode* node);
};
