#pragma once

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "Node.h"

#include <iostream>
#include <map>

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;

Value* ErrorV(const char *Str) {
    std::cout << Str << std::endl;
    return 0;
}

// generic numeric codegen for all nodes for now to see llvm codegen working
Value* PrintStmtNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* ExprStmtNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* NumberNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat((float)value_));
}

Value* StringNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* LiteralNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* BinaryNode::codegen() {
    Value* Left = left_->codegen();
    Value* Right = right_->codegen();
    if(Left != 0 && Right != 0) {
        switch(op_) {
        case TokenType::plus:
            return Builder->CreateFAdd(Left, Right, "addtmp");
        case TokenType::minus:
            return Builder->CreateFSub(Left, Right, "subtmp");
        case TokenType::mul:
            return Builder->CreateFMul(Left, Right, "multmp");

        default:
            return ErrorV("Invalid binary operation\n");
        }
    }
}

Value* UnaryNode::codegen() {
    Value *ex = expr_->codegen();
    switch(symbol_) {
        case TokenType::minus:
            return Builder->CreateFNeg(ex);
        case TokenType::not_operator:
            return Builder->CreateNot(ex);

        default:
            return ErrorV("Invalid unary expression\n");
    }
}

Value* IdentifierNode::codegen() {
    Value *V = NamedValues[value_];
    if(V) {
        return V;
    }
    else {
        return ErrorV("Unknown variable name");
    }
}

Value* GroupingNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

void GenerateCode(StmtNode *Root) {
    // Initialize LLVM context and builder
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("my_module", *TheContext);
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

    if (llvm::Value *Val = Root->codegen()) {
        // Print generated IR
        Val->print(llvm::errs());
        llvm::errs() << "\n";
    } else {
        fprintf(stderr, "Code generation failed.\n");
    }
}
