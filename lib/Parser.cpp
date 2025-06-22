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

std::list<std::shared_ptr<DeclNode>> Parser::parse() {
    std::list<std::shared_ptr<DeclNode>> declarations;
    while(!isAtEnd()) {
        std::cout << "parser here" << std::endl;
        declarations.push_back(parse_decl_());
    }
    std::cout << "parsing complete" << std::endl;
    return declarations;
}

std::shared_ptr<DeclNode> Parser::parse_decl_() {
    std::shared_ptr<DeclNode> decl(nullptr);
    if(peek() == TokenType::var_kw) {
        decl = parse_var_decl_();
    }
    else if(peek() == TokenType::func_kw) {
        decl = parse_func_decl_();
    }
    else if(peek() == TokenType::class_kw) {
        decl = parse_class_decl_();
    }
    else {
        decl = parse_stmt_();
    }
    return decl;
}

std::shared_ptr<StmtNode> Parser::parse_stmt_() {
    if(peek() == TokenType::for_kw) {
        return parse_for_stmt_();
    }
    else if(peek() == TokenType::if_kw) {
        return parse_if_stmt_();
    }
    else if(peek() == TokenType::print_kw) {
        return parse_print_stmt_();
    }
    else if(peek() == TokenType::return_kw) {
        return parse_return_stmt_();
    }
    else if(peek() == TokenType::while_kw) {
        return parse_while_stmt_();
    }
    else if(peek() == TokenType::identifier) {
        std::cout << "trying to parse assignment" << std::endl;
        return parse_assign_stmt_();
    }
    return parse_expr_stmt_();
}

std::shared_ptr<VarDeclNode> Parser::parse_var_decl_() {
    std::shared_ptr<IdentifierNode> iden(nullptr);
    std::shared_ptr<ExprStmtNode> expr(nullptr);
    std::shared_ptr<VarDeclNode> varDecl(nullptr);
    //VarDeclNode *varDecl = nullptr;

    if(match(TokenType::var_kw)) {
        if(peek() == TokenType::identifier) {
            Token t = consume();
            iden = parse_identifier(t.value_);
            if(match(TokenType::equal_assignment)) {
                expr = parse_expr_stmt_();
                if(match(TokenType::semicolon)) {
                    if(expr) {
                        varDecl = std::make_shared<VarDeclNode>(iden, expr);
                        //varDecl = new VarDeclNode(iden, expr);
                    } else {
                        std::cerr << "Error in right side expression" << std::endl;
                    }
                }
                else {
                    std::cerr << "Expected ; after expression" << std::endl;
                }
            }
            else {
                if(match(TokenType::semicolon)) {
                    varDecl = std::make_shared<VarDeclNode>(iden, nullptr);
                    //varDecl = new VarDeclNode(iden, 0);
                }
            }
        }
    }
    return varDecl;
}

std::shared_ptr<PrintStmtNode> Parser::parse_print_stmt_() {
    std::shared_ptr<PrintStmtNode> print_stmt;
    if(match(TokenType::print_kw)) {
        if(match(TokenType::open_paren)) {
            std::shared_ptr<ExprStmtNode> expr = parse_expr_stmt_();
            print_stmt = std::make_shared<PrintStmtNode>(expr);
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

std::shared_ptr<ReturnStmtNode> Parser::parse_return_stmt_() {
    std::shared_ptr<ReturnStmtNode> node = std::make_shared<ReturnStmtNode>();
    if(match(TokenType::return_kw)) {
        if(match(TokenType::semicolon)) {
            node->return_void = true;
            node->ret_expr = nullptr;
            if(match(TokenType::semicolon)) {
                return node;
            }
        }
        else {
            node->return_void = false;
            node->ret_expr = parse_expr_stmt_();
            if(match(TokenType::semicolon)) {
                return node;
            }
        }
    }
}

std::shared_ptr<LiteralNode> Parser::parse_literal_() {

}

std::shared_ptr<GroupingNode> Parser::parse_grouping_() {
    std::shared_ptr<ExprStmtNode> node = parse_expr_stmt_();
    Token next_tok = consume();
    if(next_tok.type_ != TokenType::close_paren) {
        std::cerr << "Missing )\n";
    }
    return std::make_shared<GroupingNode>(node);
}

std::shared_ptr<UnaryNode> Parser::parse_unary_(TokenType t) {
    std::shared_ptr<ExprStmtNode> node = parse_expr_stmt_();
    if(t == TokenType::minus) {
        return std::make_shared<UnaryNode>(TokenType::minus, node);
    }
    else if(t == TokenType::not_operator) {
        return std::make_shared<UnaryNode>(TokenType::not_operator, node);
    }
}

std::shared_ptr<BinaryNode> Parser::parse_binary_(std::shared_ptr<ExprStmtNode> current) {
    //ExprStmtNode *left_node = parse_expr_stmt_();
    Token op = consume();
    std::shared_ptr<ExprStmtNode> right_node = parse_expr_stmt_();

    return std::make_shared<BinaryNode>(current, right_node, op.type_);
}

std::shared_ptr<ExprStmtNode> Parser::parse_expr_stmt_() {
    //std::cout << "before, consuming, peeking - " << static_cast<int>(peek()) << std::endl;
    Token tok = consume();
    //std::cout << "after consuming, peeking - " << static_cast<int>(peek()) << std::endl;
    std::shared_ptr<ExprStmtNode> result(nullptr);
    switch(tok.type_) {
        // Literal
        case TokenType::int_numeric:
            if(peek() == TokenType::semicolon || peek() == TokenType::close_paren) {
                result = parse_number_(stoi(tok.value_));
            }
            else if(peek() == TokenType::plus || peek() == TokenType::minus ||
                    peek() == TokenType::mul || peek() == TokenType::less_than ||
                    peek() == TokenType::less_than_equal || peek() == TokenType::more_than ||
                    peek() ==  TokenType::more_than_equal || peek() == TokenType::equal_comparison ||
                    peek() ==  TokenType::not_equal_comparison) {
                result = parse_binary_(parse_number_(stoi(tok.value_)));
            }
        break;
        case TokenType::string_lit:
            result = parse_string(tok.value_);
        break;
        case TokenType::true_kw:
        case TokenType::false_kw:
        case TokenType::nil:
        break;

        case TokenType::identifier:
            std::cout << "identifier token identified" << std::endl;
            if(peek() == TokenType::semicolon || peek() == TokenType::close_paren) {
                result = parse_identifier(tok.value_);
            }
            else if(peek() == TokenType::plus || peek() == TokenType::minus ||
                    peek() == TokenType::mul || peek() == TokenType::less_than ||
                    peek() == TokenType::less_than_equal || peek() == TokenType::more_than ||
                    peek() ==  TokenType::more_than_equal || peek() == TokenType::equal_comparison ||
                    peek() ==  TokenType::not_equal_comparison) {
                result = parse_binary_(parse_identifier(tok.value_));
            }
        break;

        // Unary
        case TokenType::minus:
        case TokenType::not_operator:
            result = parse_unary_(tok.type_);
        break;

        // Grouping
        case TokenType::open_paren:
            result = parse_grouping_();
        break;

        case TokenType::close_paren:
            //continue;
        break;

        // Binary
        default:
            //std::cout << "type = " << static_cast<int>(tok.type_) << std::endl;
            result = parse_binary_(parse_number_(stoi(tok.value_)));
        break;
    }
    return result;
}

std::shared_ptr<AssignStmtNode> Parser::parse_assign_stmt_() {
    std::shared_ptr<AssignStmtNode> node = std::make_shared<AssignStmtNode>();

    node->iden = parse_identifier(consume().value_);
    std::cout << "iden parsed haah" << node->iden->value_ <<  std::endl;

    if(match(TokenType::equal_assignment)) {
        node->exprStmt = parse_expr_stmt_();
        std::cout << "expr parsed" << std::endl;
        if(peek() == TokenType::semicolon) {
            consume();
        }
        else {
            std::cerr << "Missing semicolon" << std::endl;
        }
    }
    else {
        std::cerr << "Missing \'=\' in assignment statement" << std::endl;
    }

    return node;
}

// TODO: Error handling
std::shared_ptr<ForStmtNode> Parser::parse_for_stmt_() {
    std::shared_ptr<ForStmtNode> node = std::make_shared<ForStmtNode>();
    if(match(TokenType::for_kw)) {
        if(match(TokenType::open_paren)) {
            node->init = parse_var_decl_();
            if(match(TokenType::semicolon)) {
                node->condition = parse_expr_stmt_();
                if(match(TokenType::semicolon)) {
                    node->update = parse_expr_stmt_();
                    if(match(TokenType::close_paren)) {
                        node->loop_block = parse_block_();
                    }
                }
            }
        }
    }
    //else {
    //}
    return node;
}

// TODO: Error handling
std::shared_ptr<IfStmtNode> Parser::parse_if_stmt_() {
    std::shared_ptr<IfStmtNode> node = std::make_shared<IfStmtNode>();
    if(match(TokenType::if_kw)) {
        if(match(TokenType::open_paren)) {
            node->if_expr = parse_expr_stmt_();
            if(match(TokenType::close_paren)) {
                node->if_block = parse_block_();
                if(match(TokenType::else_kw)) {
                    std::cout << "else block exists" << std::endl;
                    node->else_block = parse_block_();
                    std::cout << "else block parsed" << std::endl;
                }
                else {
                    std::cout << "else block doesn't exist in this case" << std::endl;
                    node->else_expr = nullptr;
                    node->else_block = nullptr;
                }
            }
        }
    }
    return node;
}

// TODO: Error handling
std::shared_ptr<WhileStmtNode> Parser::parse_while_stmt_() {
    std::shared_ptr<WhileStmtNode> node = std::make_shared<WhileStmtNode>();
    if(match(TokenType::while_kw)) {
        if(match(TokenType::open_paren)) {
            node->conditional_expr = parse_expr_stmt_();
            if(match(TokenType::close_paren)) {
                node->loop_block = parse_block_();
            }
        }
    }
    return node;
}

// TODO: Error handling and testing
std::shared_ptr<FuncDeclNode> Parser::parse_func_decl_() {
    std::shared_ptr<FuncDeclNode> node = std::make_shared<FuncDeclNode>();
    if(match(TokenType::func_kw)) {
        if(peek() == TokenType::identifier) {
            Token t = consume();
            node->func_iden = parse_identifier(t.value_);
            if(match(TokenType::open_paren)) {
                if(match(TokenType::close_paren)) {
                    node->empty_param = true;
                    node->params = nullptr;
                    if(peek() == TokenType::open_curly) {
                        node->func_block = parse_block_();
                    }
                }
                else {
                    node->empty_param = false;
                    node->params = parse_params_();
                    if(match(TokenType::close_paren)) {
                        if(peek() == TokenType::open_curly) {
                            node->func_block = parse_block_();
                        }
                    }
                }
            }
        }
    }
    return node;
}

std::shared_ptr<ClassDeclNode> Parser::parse_class_decl_() {

}

std::shared_ptr<ParametersNode> Parser::parse_params_() {

}

std::shared_ptr<BlockNode> Parser::parse_block_() {
    std::cout << "parsing block" << std::endl;
    std::shared_ptr<BlockNode> node = std::make_shared<BlockNode>();

    if(match(TokenType::open_curly)) {
        while(peek() != TokenType::close_curly) {
            node->declarations.push_back(parse_decl_());
        }
        if(match(TokenType::close_curly)) {
            //std::cout << "exiting block" << std::endl;
            return node;
        }
        else {
            std::cerr << "Missing } in the block" << std::endl;
        }
    }
    else {
        //std::cerr << "type: " << static_cast<int>(peek()) << std::endl;
        std::cerr << "Missing { in the Block" << std::endl;
    }
}


std::shared_ptr<NumberNode> Parser::parse_number_(int num) {
    std::shared_ptr<NumberNode> node = std::make_shared<NumberNode>(num);
    return node;
}

std::shared_ptr<StringNode> Parser::parse_string(std::string str) {
    std::shared_ptr<StringNode> node = std::make_shared<StringNode>(str);
    return node;
}

std::shared_ptr<IdentifierNode> Parser::parse_identifier(std::string str) {
    std::shared_ptr<IdentifierNode> node = std::make_shared<IdentifierNode>(str);
    return node;
}

/***LiteralNode* Parser::parse_literal(ExprStmtNode* node) {
    LiteralNode* literal_node = new LiteralNode(node);
    return literal_node;
}***/
