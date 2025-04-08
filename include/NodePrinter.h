#pragma once

#include "Node.h"

#include <iostream>

class NodePrinter {
public:
    void printExpr(ExprStmtNode *node);
    void printUnary(UnaryNode *node);
    void printBinary(BinaryNode *node);
    void printNumber(NumberNode *node);
    void printString(StringNode *node);
    void printIdentifier(IdentifierNode *node);
};
