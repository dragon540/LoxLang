#pragma once

#include <vector>

#include "Lexer.h"
#include "Token.h"
#include "TokenType.h"
#include "Node.h"


class Parser {
public:
    Parser(std::vector<Token> tokens);
    void parse();

private:
    std::vector<Token> tokens_;
    unsigned int current_idx = 0;

    bool isAtEnd();

    Token consume();
    TokenType peek();

    void parseToken();

    void parse_expr_();
    void parse_literal_();
    void parse_unary_();
    void parse_binary_();
    void parse_grouping_();
    void parse_operator_();
};
