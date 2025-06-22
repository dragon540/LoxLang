#pragma once

#include "Node.h"

#include <iostream>

class NodePrinter {
public:
    void printProgram();
    void printDeclaration(std::shared_ptr<DeclNode> node);
    void printStatement(std::shared_ptr<StmtNode> node);
    void printExprStmt(std::shared_ptr<ExprStmtNode> node);
    void printAssignStmt(std::shared_ptr<AssignStmtNode> node);
    void printForStmt(std::shared_ptr<ForStmtNode> node);
    void printIfStmt(std::shared_ptr<IfStmtNode> node);
    void printAssignStmt(std::shared_ptr<PrintStmtNode> node);
    void printReturnStmt(std::shared_ptr<ReturnStmtNode> node);
    void printPrintStmt(std::shared_ptr<PrintStmtNode> node);
    void printWhileStmt(std::shared_ptr<WhileStmtNode> node);
    void printBlock(std::shared_ptr<BlockNode> node);
    void printLiteral(std::shared_ptr<LiteralNode> node);
    void printGrouping(std::shared_ptr<GroupingNode> node);
    void printUnary(std::shared_ptr<UnaryNode> node);
    void printBinary(std::shared_ptr<BinaryNode> node);
    void printNumber(std::shared_ptr<NumberNode> node);
    void printString(std::shared_ptr<StringNode> node);
    void printIdentifier(std::shared_ptr<IdentifierNode> node);
    void printVarDecl(std::shared_ptr<VarDeclNode> node);
    void printFuncDecl(std::shared_ptr<FuncDeclNode> node);
    void printClassDecl(std::shared_ptr<ClassDeclNode> node);
};
