#include "Parser.h"

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

// consume current token if it matches t
bool Parser::match(TokenType t) {
    if(peek() == t) {
        consume();
        return true;
    }
    return false;
}

/**void Parser::parse() {
    ExprNode* exprNode;
    exprNode = parse_expr_();
    std::cout << exprNode << std::endl;
    std::cout << "bp 1\n";
    NodePrinter np;
    np.printExpr(exprNode);
    std::cout << "bp 2\n";

    GenerateCode(exprNode);
    std::cout << "bp 3\n";
}**/

/**
void Parser::parseToken() {
    parse_expr_();
}
**/

std::list<DeclNode*> Parser::parse() {
    std::list<DeclNode*> declarations;
    while(!isAtEnd()) {
        std::cout << "parser here" << std::endl;
        declarations.push_back(parse_decl_());
    }
    std::cout << "parsing complete" << std::endl;
    return declarations;
}

DeclNode* Parser::parse_decl_() {
    DeclNode *decl;
    if(peek() == TokenType::var_kw) {
        decl = parse_var_decl_();
    }
    else {
        decl = parse_stmt_();
    }
    return decl;
}

VarDeclNode* Parser::parse_var_decl_() {
    IdentifierNode *iden = nullptr;
    ExprStmtNode *expr = nullptr;
    VarDeclNode *varDecl = nullptr;

    if(match(TokenType::var_kw)) {
        if(peek() == TokenType::identifier) {
            Token t = consume();
            iden = parse_identifier(t.value_);
            if(match(TokenType::equal_assignment)) {
                expr = parse_expr_stmt_();
                if(match(TokenType::semicolon)) {
                    varDecl = new VarDeclNode(iden, expr);
                }
                else {
                    std::cout << "Expected ; after expression" << std::endl;
                    delete expr;
                }
            }
            else {
                if(match(TokenType::semicolon)) {
                    varDecl = new VarDeclNode(iden, 0);
                }
            }
        }
    }
    return varDecl;
}

StmtNode* Parser::parse_stmt_() {
    if(peek() == TokenType::print_kw) {
        return parse_print_stmt_();
    }
    return parse_expr_stmt_();
}

PrintStmtNode* Parser::parse_print_stmt_() {
    PrintStmtNode* print_stmt;
    if(match(TokenType::print_kw)) {
        if(match(TokenType::open_paren)) {
            ExprStmtNode *expr = parse_expr_stmt_();
            print_stmt = new PrintStmtNode(expr);
            if(match(TokenType::close_paren)) {
                if(match(TokenType::semicolon)) {
                    return print_stmt;
                }
                else {
                    std::cout << "Error: Missing semicolon after )" << std::endl;
                }
            }
            else {
                std::cout << "Error: Missing ) after expression" << std::endl;
            }
        }
        else {
            std::cout << "Error: Missing ( after print keyword" << std::endl;
        }
    }
}

ExprStmtNode* Parser::parse_expr_stmt_() {
    Token tok = consume();
    ExprStmtNode* result = nullptr;
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
            ExprStmtNode *node = parse_expr_stmt_();
            result = new UnaryNode(TokenType::minus, node);
    }
        break;
        case TokenType::not_operator:
    {
            ExprStmtNode *node = parse_expr_stmt_();
            result = new UnaryNode(TokenType::not_operator, node);
    }
        break;

        // Grouping
        case TokenType::open_paren:
    {
            ExprStmtNode *node = parse_expr_stmt_();
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

LiteralNode* Parser::parse_literal(ExprStmtNode* node) {
    LiteralNode* literal_node = new LiteralNode(node);
    return literal_node;
}
