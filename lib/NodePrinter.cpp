#include "NodePrinter.h"

void printDeclaration(DeclNode *node);
void PrintStatement(StmtNode *node);

void NodePrinter::printExprStmt(ExprStmtNode *node) {
        if (auto str = dynamic_cast<StringNode*>(node)) {
            printString(str);
        } else if(auto iden = dynamic_cast<IdentifierNode*>(node)) {
            printIdentifier(iden);
        } else if (auto bin = dynamic_cast<BinaryNode*>(node)) {
            printBinary(bin);
        } else if (auto unary = dynamic_cast<UnaryNode*>(node)) {
            printUnary(unary);
        } else {
            std::cout << "Unknown expression";
        }
}

void printForStmt(ForStmtNode *node);
void printIfStmt(IfStmtNode *node);
void printPrintStmt(PrintStmtNode *node);
void printReturnStmt(ReturnStmtNode *node);
void printWhileStmt(WhileStmtNode *node);
void printBlock(BlockNode *node);
void printLiteral(LiteralNode *node);
void printGrouping(GroupingNode *node);

void NodePrinter::printUnary(UnaryNode *node) {
    std::cout << "( " << static_cast<int>(node->symbol_) << " ";
    printExprStmt(node->expr_);
    std::cout  << " ) ";

}

void NodePrinter::printBinary(BinaryNode *node) {
    std::cout << "( ";
    printExprStmt(node->left_);
    std:: cout << " ( " << static_cast<int>(node->op_) << " ) ";
    printExprStmt(node->right_);
    std::cout << " ) ";
}

//void NodePrinter::printNumber() {
//
//}

void NodePrinter::printString(StringNode *node) {
    std::cout << "( " << node->value_ << " ) ";
}

void NodePrinter::printIdentifier(IdentifierNode *node) {
    std::cout << "( " << node->value_ << " ) ";
}
