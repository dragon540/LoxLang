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

    std::list<std::shared_ptr<DeclNode>> parse();

private:
    std::vector<Token> tokens_;
    unsigned int current_idx = 0;

    bool isAtEnd();

    Token consume();
    TokenType peek();
    bool match(TokenType t);

    void parseToken();

    //std::list<StmtNode*> parse();
    std::shared_ptr<DeclNode> parse_decl_();
    std::shared_ptr<StmtNode> parse_stmt_();
    std::shared_ptr<ExprStmtNode> parse_expr_stmt_();
    std::shared_ptr<AssignStmtNode> parse_assign_stmt_();
    std::shared_ptr<ForStmtNode> parse_for_stmt_();
    std::shared_ptr<IfStmtNode> parse_if_stmt_();
    std::shared_ptr<PrintStmtNode> parse_print_stmt_();
    std::shared_ptr<ReturnStmtNode> parse_return_stmt_();
    std::shared_ptr<WhileStmtNode> parse_while_stmt_();
    std::shared_ptr<BlockNode> parse_block_();
    std::shared_ptr<LiteralNode> parse_literal_();
    std::shared_ptr<GroupingNode> parse_grouping_();
    std::shared_ptr<UnaryNode> parse_unary_(TokenType t);
    std::shared_ptr<BinaryNode> parse_binary_(std::shared_ptr<ExprStmtNode> current);
    std::shared_ptr<VarDeclNode> parse_var_decl_();
    std::shared_ptr<FuncDeclNode> parse_func_decl_();
    std::shared_ptr<ClassDeclNode> parse_class_decl_();
    std::shared_ptr<ParametersNode> parse_params_();
    void parse_operator_();
    std::shared_ptr<NumberNode> parse_number_(int num);
    std::shared_ptr<StringNode> parse_string(std::string str);
    std::shared_ptr<IdentifierNode> parse_identifier(std::string str);
};
