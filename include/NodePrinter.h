#pragma once

#include "Node.h"

#include <iostream>

class NodePrinter {
public:
    void printProgram();
    void printDeclaration(DeclNode *node);
    void printStatement(StmtNode *node);
    void printExprStmt(ExprStmtNode *node);
    void printForStmt(ForStmtNode *node);
    void printIfStmt(IfStmtNode *node);
    void printPrintStmt(PrintStmtNode *node);
    void printReturnStmt(ReturnStmtNode *node);
    void printWhileStmt(WhileStmtNode *node);
    void printBlock(BlockNode *node);
    void printLiteral(LiteralNode *node);
    void printGrouping(GroupingNode *node);
    void printUnary(UnaryNode *node);
    void printBinary(BinaryNode *node);
    void printNumber(NumberNode *node);
    void printString(StringNode *node);
    void printIdentifier(IdentifierNode *node);
    void printVarDecl(VarDeclNode *node);
    void printFuncDecl(FuncDeclNode *node);
    void printClassDecl(ClassDeclNode *node);
};
