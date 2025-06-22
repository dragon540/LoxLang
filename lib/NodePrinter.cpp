#include "NodePrinter.h"

unsigned int tab = 0;

void NodePrinter::printDeclaration(std::shared_ptr<DeclNode> node) {
    if(auto var = std::dynamic_pointer_cast<VarDeclNode>(node)) {
        printVarDecl(var);
    }
    else if(auto func = std::dynamic_pointer_cast<FuncDeclNode>(node)) {
        printFuncDecl(func);
    }
    else if(auto cls = std::dynamic_pointer_cast<ClassDeclNode>(node)) {
        printClassDecl(cls);
    }
    else if(auto stmt = std::dynamic_pointer_cast<StmtNode>(node)) {
        printStatement(stmt);
    }
    else {
        std::cerr << "Unrecognizable declaration" << std::endl;
    }
}

void NodePrinter::printStatement(std::shared_ptr<StmtNode> node) {
    if(auto expr = std::dynamic_pointer_cast<ExprStmtNode>(node)) {
        printExprStmt(expr);
    }
    else if(auto assignStmt = std::dynamic_pointer_cast<AssignStmtNode>(node)) {
        printAssignStmt(assignStmt);
    }
    else if(auto forStmt = std::dynamic_pointer_cast<ForStmtNode>(node)) {
        printForStmt(forStmt);
    }
    else if(auto ifStmt = std::dynamic_pointer_cast<IfStmtNode>(node)) {
        printIfStmt(ifStmt);
    }
    else if(auto printStmt = std::dynamic_pointer_cast<PrintStmtNode>(node)) {
        printPrintStmt(printStmt);
    }
    else if(auto ret = std::dynamic_pointer_cast<ReturnStmtNode>(node)) {
        printReturnStmt(ret);
    }
    else if(auto whileStmt = std::dynamic_pointer_cast<WhileStmtNode>(node)) {
        printWhileStmt(whileStmt);
    }
    else if(auto block = std::dynamic_pointer_cast<BlockNode>(node)) {
        printBlock(block);
    }
    else {
        std::cerr << "Unrecognizable statement type" << std::endl;
    }
}

void NodePrinter::printExprStmt(std::shared_ptr<ExprStmtNode> node) {
    //std::cout << "actual runtime type: " << typeid(*node).name() << std::endl;
        if (auto str = std::dynamic_pointer_cast<StringNode>(node)) {
            printString(str);
        } else if(auto num = std::dynamic_pointer_cast<NumberNode>(node)) {
            printNumber(num);
        // TODO : something wrong with identifier type, revisit fom here
        } else if(auto iden = std::dynamic_pointer_cast<IdentifierNode>(node)) {
            printIdentifier(iden);
        } else if (auto bin = std::dynamic_pointer_cast<BinaryNode>(node)) {
            printBinary(bin);
        } else if (auto unary = std::dynamic_pointer_cast<UnaryNode>(node)) {
            printUnary(unary);
        } else {
            std::cerr << "Unknown expression" << std::endl;
        }
}

void NodePrinter::printAssignStmt(std::shared_ptr<AssignStmtNode> node) {
    std::cout << "( ";
    printIdentifier(node->iden);
    printExprStmt(node->exprStmt);
    std::cout << " )";
}

void NodePrinter::printForStmt(std::shared_ptr<ForStmtNode> node) {
    std::cout << "( ";
    printVarDecl(node->init);
    printExprStmt(node->condition);
    printExprStmt(node->update);
    printBlock(node->loop_block);
    std::cout << " )";
}

void NodePrinter::printIfStmt(std::shared_ptr<IfStmtNode> node) {
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

void NodePrinter::printPrintStmt(std::shared_ptr<PrintStmtNode> node) {
    std::cout << "for now just print" << std::endl;
}

void NodePrinter::printReturnStmt(std::shared_ptr<ReturnStmtNode> node) {
    std::cout << "( ";
    if(node->return_void == true) {
        std::cout << " )";
    }
    else {
        printExprStmt(node->ret_expr);
    }
    std::cout << " )";
}

void NodePrinter::printWhileStmt(std::shared_ptr<WhileStmtNode> node) {
    std::cout << "( ";
    printExprStmt(node->conditional_expr);
    printBlock(node->loop_block);
    std::cout << " )";
}

void NodePrinter::printBlock(std::shared_ptr<BlockNode> node) {
    std::cout << "( ";
    //std::cout << "working till here" << std::endl;
    for(auto & i : node->declarations) {
        printDeclaration(i);
    }
    std::cout << " )";
}

void NodePrinter::printLiteral(std::shared_ptr<LiteralNode> node) {

}

void NodePrinter::printGrouping(std::shared_ptr<GroupingNode> node) {

}

void NodePrinter::printUnary(std::shared_ptr<UnaryNode> node) {
    std::cout << "( " << static_cast<int>(node->symbol_) << " ";
    printExprStmt(node->expr_);
    std::cout  << " )";

}

void NodePrinter::printBinary(std::shared_ptr<BinaryNode> node) {
    //std::cout << "printing Binary" << std::endl;
    std::cout << "( ";
    printExprStmt(node->left_);
    std:: cout << " ( " << static_cast<int>(node->op_) << " ) ";
    printExprStmt(node->right_);
    std::cout << " ) ";
}

void NodePrinter::printVarDecl(std::shared_ptr<VarDeclNode> node) {
    std::cout << "( ";
    printIdentifier(node->iden);
    printExprStmt(node->expr);
    std::cout << " )";
}

// TODO:
void NodePrinter::printFuncDecl(std::shared_ptr<FuncDeclNode> node) {
    std::cout << "( ";
}

// TODO:
void NodePrinter::printClassDecl(std::shared_ptr<ClassDeclNode> node) {
    std::cout << "( ";
}

void NodePrinter::printNumber(std::shared_ptr<NumberNode> node) {
    std::cout << "( " << node->value_ << " )";
}

void NodePrinter::printString(std::shared_ptr<StringNode> node) {
    std::cout << "( " << node->value_ << " )";
}

void NodePrinter::printIdentifier(std::shared_ptr<IdentifierNode> node) {
    std::cout << "( " << node->value_ << " )";
}
