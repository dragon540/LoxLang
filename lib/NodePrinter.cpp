#include "NodePrinter.h"

void NodePrinter::printExpr(ExprStmtNode *node) {
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

void NodePrinter::printUnary(UnaryNode *node) {
    std::cout << "( " << static_cast<int>(node->symbol_) << " ";
    printExpr(node->expr_);
    std::cout  << " ) ";

}

void NodePrinter::printBinary(BinaryNode *node) {
    std::cout << "( ";
    printExpr(node->left_);
    std:: cout << " ( " << static_cast<int>(node->op_) << " ) ";
    printExpr(node->right_);
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
