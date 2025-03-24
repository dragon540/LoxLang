#pragma once

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "Node.h"

#include <map>

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;

// generic numeric codegen for all nodes for now to see llvm codegen working

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
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* UnaryNode::codegen() {
    Value *ex = expr_->codegen();
    return Builder->CreateFMul(ex, ex, "multmp");
}

Value* IdentifierNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* GroupingNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

void GenerateCode(ExprNode *Root) {
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
