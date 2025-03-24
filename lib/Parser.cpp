#include "Parser.h"

#include "Driver.h"


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
    ExprNode* exprNode;
    exprNode = parse_expr_();
    std::cout << exprNode << std::endl;

    NodePrinter np;
    np.printExpr(exprNode);

    GenerateCode(exprNode);

}

/**
void Parser::parseToken() {
    parse_expr_();
}
**/

ExprNode* Parser::parse_expr_() {
    Token tok = consume();
    ExprNode* result = nullptr;
    switch(tok.type_) {
        // Literal
        case TokenType::int_numeric:
            result = parse_number_(stoi(tok.value_));
        break;
        case TokenType::string_lit:
            result = parse_string(tok.value_);
        break;
        case TokenType::true_kw:
        case TokenType::false_kw:
        case TokenType::nil:
        break;

        // Unary
        case TokenType::minus:
    {
            ExprNode *node = parse_expr_();
            result = new UnaryNode(TokenType::minus, node);
    }
        break;
        case TokenType::not_operator:
    {
            ExprNode *node = parse_expr_();
            result = new UnaryNode(TokenType::not_operator, node);
    }
        break;

        // Grouping
        case TokenType::open_paren:
    {
            ExprNode *node = parse_expr_();
            Token next_tok = consume();
            if(next_tok.type_ != TokenType::close_paren) {
                std::cout << "Missing )\n";
                break;
            }
            result = new GroupingNode(node);
    }
        break;

        case TokenType::close_paren:
            //continue;
        break;

        // Binary

    }
    return result;
}

NumberNode* Parser::parse_number_(int num) {
    NumberNode* node = new NumberNode(num);
    return node;
}

StringNode* Parser::parse_string(std::string str) {
    StringNode* node = new StringNode(str);
    return node;
}

IdentifierNode* Parser::parse_identifier(std::string str) {
    IdentifierNode* node = new IdentifierNode(str);
    return node;
}

LiteralNode* Parser::parse_literal(ExprNode* node) {
    LiteralNode* literal_node = new LiteralNode(node);
    return literal_node;
}
