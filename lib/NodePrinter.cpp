#include "NodePrinter.h"

unsigned int tab = 0;

void NodePrinter::printDeclaration(DeclNode *node) {
    if(auto var = dynamic_cast<VarDeclNode*>(node)) {
        printVarDecl(var);
    }
    else if(auto func = dynamic_cast<FuncDeclNode*>(node)) {
        printFuncDecl(func);
    }
    else if(auto cls = dynamic_cast<ClassDeclNode*>(node)) {
        printClassDecl(cls);
    }
    else if(auto stmt = dynamic_cast<StmtNode*>(node)) {
        printStatement(stmt);
    }
    else {
        std::cerr << "Unrecognizable declaration" << std::endl;
    }
}

void NodePrinter::printStatement(StmtNode *node) {
    if(auto expr = dynamic_cast<ExprStmtNode*>(node)) {
        printExprStmt(expr);
    }
    else if(auto assignStmt = dynamic_cast<AssignStmtNode*>(node)) {
        printAssignStmt(assignStmt);
    }
    else if(auto forStmt = dynamic_cast<ForStmtNode*>(node)) {
        printForStmt(forStmt);
    }
    else if(auto ifStmt = dynamic_cast<IfStmtNode*>(node)) {
        printIfStmt(ifStmt);
    }
    else if(auto printStmt = dynamic_cast<PrintStmtNode*>(node)) {
        printPrintStmt(printStmt);
    }
    else if(auto ret = dynamic_cast<ReturnStmtNode*>(node)) {
        printReturnStmt(ret);
    }
    else if(auto whileStmt = dynamic_cast<WhileStmtNode*>(node)) {
        printWhileStmt(whileStmt);
    }
    else if(auto block = dynamic_cast<BlockNode*>(node)) {
        printBlock(block);
    }
    else {
        std::cerr << "Unrecognizable statement type" << std::endl;
    }
}

void NodePrinter::printExprStmt(ExprStmtNode *node) {
    //std::cout << "actual runtime type: " << typeid(*node).name() << std::endl;
        if (auto str = dynamic_cast<StringNode*>(node)) {
            printString(str);
        } else if(auto num = dynamic_cast<NumberNode*>(node)) {
            printNumber(num);
        // TODO : something wrong with identifier type, revisit fom here
        } else if(auto iden = dynamic_cast<IdentifierNode*>(node)) {
            printIdentifier(iden);
        } else if (auto bin = dynamic_cast<BinaryNode*>(node)) {
            printBinary(bin);
        } else if (auto unary = dynamic_cast<UnaryNode*>(node)) {
            printUnary(unary);
        } else {
            std::cerr << "Unknown expression" << std::endl;
        }
}

void NodePrinter::printAssignStmt(AssignStmtNode *node) {
    std::cout << "( ";
    printIdentifier(node->iden);
    printExprStmt(node->exprStmt);
    std::cout << " )";
}

void NodePrinter::printForStmt(ForStmtNode *node) {
    std::cout << "( ";
    printVarDecl(node->init);
    printExprStmt(node->condition);
    printExprStmt(node->update);
    printBlock(node->loop_block);
    std::cout << " )";
}

void NodePrinter::printIfStmt(IfStmtNode *node) {
    //std::cout << "printing IfStmt" << std::endl;
    std::cout << "( ";
    printExprStmt(node->if_expr);
    printBlock(node->if_block);
    if(node->else_expr != nullptr) {
        printExprStmt(node->else_expr);
        printBlock(node->else_block);
    }
    std::cout << " )";
}

void NodePrinter::printPrintStmt(PrintStmtNode *node) {
    std::cout << "for now just print" << std::endl;
}

void NodePrinter::printReturnStmt(ReturnStmtNode *node) {
    std::cout << "( ";
    if(node->return_void == true) {
        std::cout << " )";
    }
    else {
        printExprStmt(node->ret_expr);
    }
    std::cout << " )";
}

void NodePrinter::printWhileStmt(WhileStmtNode *node) {
    std::cout << "( ";
    printExprStmt(node->conditional_expr);
    printBlock(node->loop_block);
    std::cout << " )";
}

void NodePrinter::printBlock(BlockNode *node) {
    std::cout << "( ";
    //std::cout << "working till here" << std::endl;
    for(auto & i : node->declarations) {
        printDeclaration(i);
    }
    std::cout << " )";
}

void NodePrinter::printLiteral(LiteralNode *node) {

}

void NodePrinter::printGrouping(GroupingNode *node) {

}

void NodePrinter::printUnary(UnaryNode *node) {
    std::cout << "( " << static_cast<int>(node->symbol_) << " ";
    printExprStmt(node->expr_);
    std::cout  << " )";

}

void NodePrinter::printBinary(BinaryNode *node) {
    //std::cout << "printing Binary" << std::endl;
    std::cout << "( ";
    printExprStmt(node->left_);
    std:: cout << " ( " << static_cast<int>(node->op_) << " ) ";
    printExprStmt(node->right_);
    std::cout << " ) ";
}

void NodePrinter::printVarDecl(VarDeclNode *node) {
    std::cout << "( ";
    printIdentifier(node->iden);
    printExprStmt(node->expr);
    std::cout << " )";
}

// TODO:
void NodePrinter::printFuncDecl(FuncDeclNode *node) {
    std::cout << "( ";
}

// TODO:
void NodePrinter::printClassDecl(ClassDeclNode *node) {
    std::cout << "( ";
}

void NodePrinter::printNumber(NumberNode *node) {
    std::cout << "( " << node->value_ << " )";
}

void NodePrinter::printString(StringNode *node) {
    std::cout << "( " << node->value_ << " )";
}

void NodePrinter::printIdentifier(IdentifierNode *node) {
    std::cout << "( " << node->value_ << " )";
}
