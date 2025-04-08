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

Value* VarDeclNode::codegen() {
    std::cout << "var decl codegen" << std::endl;
    std::cout << iden->value_.c_str() << std::endl;
    if(Builder->GetInsertBlock() == nullptr) {
        std::cout << "not inside any basic block" << std::endl;
    }
    AllocaInst *Alloca = Builder->CreateAlloca(Type::getInt32Ty(*TheContext), nullptr, (iden->value_).c_str());
    std::cout << "alloca" << std::endl;

    if(expr) {
        Value *val = expr->codegen();
        if(!val) {
            std::cout << "nullptr" << std::endl;
            return nullptr;
        }
        Builder->CreateStore(val, Alloca);
    }

    NamedValues[iden->value_] = Alloca;
    return Alloca;
}

Value* PrintStmtNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* ExprStmtNode::codegen() {
    return ConstantInt::get(*TheContext, APInt(32, 53));
}

Value* NumberNode::codegen() {
    return ConstantInt::get(*TheContext, APInt(32, value_));
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
    if(ex) {
        switch(symbol_) {
            case TokenType::minus:
                return Builder->CreateFNeg(ex);
            case TokenType::not_operator:
                return Builder->CreateNot(ex);

            default:
                return ErrorV("Invalid unary expression\n");
        }
    }
}

Value* IdentifierNode::codegen() {
    std::cout << "ident codegen" << std::endl;
    Value *V = NamedValues[value_];
    std::cout << "opsdfcd" << std::endl;
    if(V) {
        return Builder->CreateLoad(Type::getDoubleTy(*TheContext), V, value_.c_str());
    }
    else {
        return ErrorV("Unknown variable name");
    }
}

Value* GroupingNode::codegen() {
    return exprStmt->codegen();
}

void GenerateCode(DeclNode *Root) {
    // Initialize LLVM context and builder
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("my_module", *TheContext);
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

    // Create a dummy function to hold top-level code
    FunctionType *funcType = FunctionType::get(Type::getVoidTy(*TheContext), false);
    Function *mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", TheModule.get());

    // Create an entry block for the function
    BasicBlock *entry = BasicBlock::Create(*TheContext, "entry", mainFunc);
    Builder->SetInsertPoint(entry);

    std::cout << "fhdjsk" << std::endl;
    if (llvm::Value *Val = Root->codegen()) {
        // Print generated IR
        Val->print(llvm::errs());
        llvm::errs() << "\n";

        // Finish off the function with a return void
        Builder->CreateRetVoid();
    } else {
        fprintf(stderr, "Code generation failed.\n");
    }
}
