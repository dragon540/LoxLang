#include "Parser.h"

/***
Parser::Parser(std::vector<Token> tokens)
    :tokens_(tokens) {}

bool Parser::isAtEnd() {
    if(current_idx < tokens_.size()) {
        return false;
    }
    return true;
}

// returns current token from token list
// and moves current_idx to next token in the list
Token Parser::consume() {
    current_idx++;
    return tokens_[current_idx - 1];
}

TokenType Parser::peek() {
    if(!isAtEnd()) {
        return tokens_[current_idx].type_;
    }
    return TokenType::eof;
}

void Parser::parse() {
    while(!isAtEnd()) {
        parseToken();
    }
}

void Parser::parseToken() {
    parse_expr_();
}

void Parser::parse_expr_() {
    Token tok = consume();
    switch(tok.type_) {
        // Literal
        case TokenType::int_numeric:
            NumberNode(tok.value_);
        break;
        //case TokenType::decimal_numeric:
        case TokenType::string_lit:
            StringNode(tok.value_);
        break;
        case TokenType::true_kw:
        case TokenType::false_kw:
        case TokenType::nil:
        break;

        // Unary
        case TokenType::minus:
            ASTNode *node = new parse_expr_();
            Unary(TokenType::minus, node);
        break;
        case TokenType::not_operator:
            ASTNode *node = new parse_expr_();
            Unary(TokenType::not_operator, node);
        break;

        // Grouping
        case TokenType::open_paren:
            ASTNode *node = new parse_expr_();
            Grouping(node);
        break;

        case TokenType::close_paren:
            continue;
        break;



        // Binary
    }
}
***/
