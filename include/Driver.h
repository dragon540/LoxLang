#pragma once

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "Node.h"

#include <iostream>
#include <map>
#include <typeinfo>

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;

Value* ErrorV(std::string Str) {
    std::cout << Str << std::endl;
    return 0;
}

// generic numeric codegen for all nodes for now to see llvm codegen working

// Working:
// Since we are declaring variable here, basically we need to allocate some
// space on stack, then store the value;
Value* VarDeclNode::codegen() {
    std::cout << "variable declaration codegen :" << std::endl;
    std::cout << "Identifier name: " << iden->value_.c_str() << std::endl;
    if(Builder->GetInsertBlock() == nullptr) {
        std::cout << "not inside any basic block" << std::endl;
    }
    AllocaInst *Alloca = Builder->CreateAlloca(Type::getInt32Ty(*TheContext), nullptr, (iden->value_).c_str());
    //std::cout << "alloca" << std::endl;

    if(expr) {
        //std::cout << "expr is valid" << std::endl;
        //std::cout << "actual runtime type: " << typeid(*expr).name() << std::endl;
        Value *val = expr->codegen();
        //std::cout << "expr->codegen() should have been called before this line" << std::endl;
        std::cout << "pcmviewnr" << std::endl;
        if(!val) {
            std::cout << "nullptr" << std::endl;
            return nullptr;
        }
        std::cout << "jujfehdiw haha" << std::endl;
        Builder->CreateStore(val, Alloca);
    }

    NamedValues[iden->value_] = Alloca;
    return Alloca;
}

Value* FuncDeclNode::codegen() {
}

Value* ClassDeclNode::codegen() {

}

Value* BlockNode::codegen() {
    for(auto & i : statements) {
        i->codegen();
    }
}

Value* ParametersNode::codegen() {
    for(auto & i : identifiers) {
        i->codegen();
    }
}

/**Value* IfStmtNode::codegen() {
    return Builder->CreateCondBr(if_expr->codegen(), if_block, else_block);
}**/

Value* ReturnStmtNode::codegen() {

}

Value* WhileStmtNode::codegen() {

}

Value* IfStmtNode::codegen() {

}

Value* ForStmtNode::codegen() {

}

Value* PrintStmtNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* ExprStmtNode::codegen() {
    return ConstantInt::get(*TheContext, APInt(32, 53));
}

Value* NumberNode::codegen() {
    //std::cout << "we are here\n";
    return ConstantInt::get(*TheContext, APInt(32, value_));
}

Value* StringNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* LiteralNode::codegen() {
    return ConstantFP::get(*TheContext, APFloat(1.5));
}

Value* BinaryNode::codegen() {
    //std::cout << "we are in binary codegen" << std::endl;
    Value* Left = left_->codegen();
    Value* Right = right_->codegen();
    if(!Builder) {
        std::cerr << "Something wrong with builder in BinaryNode::codegen()" << std::endl;
    }
    if(Left != 0 && Right != 0) {
        switch(op_) {
        case TokenType::plus:
            return Builder->CreateAdd(Left, Right, "addtmp");
        case TokenType::minus:
            return Builder->CreateSub(Left, Right, "subtmp");
        case TokenType::mul:
            return Builder->CreateMul(Left, Right, "multmp");
        case TokenType::less_than:
            return Builder->CreateICmpULT(Left, Right);
        case TokenType::less_than_equal:
            return Builder->CreateICmpULE(Left, Right);
        case TokenType::more_than:
            return Builder->CreateICmpUGT(Left, Right);
        case TokenType::more_than_equal:
            return Builder->CreateICmpUGE(Left, Right);
        case TokenType::equal_comparison:
            return Builder->CreateICmpEQ(Left, Right);
        case TokenType::not_equal_comparison:
            return Builder->CreateICmpNE(Left, Right);
        default:
            return ErrorV("Invalid binary operator\n");
        }
    }
    return ErrorV("Invalid binary operation\n");
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

// Working:
// codegen for variable allocation, only allocates space in memory for the variable
// TODO: currently all IR generations are carried out in seperate module, change it.
Value* IdentifierNode::codegen() {
    if(Builder->GetInsertBlock() == nullptr) {
        std::cout << "not inside any basic block" << std::endl;
    }
    if(NamedValues.find(value_) != NamedValues.end()) {
        AllocaInst *Alloca = Builder->CreateAlloca(Type::getInt32Ty(*TheContext), nullptr, value_.c_str());
        NamedValues[value_] = Alloca;
        return Alloca;
    }
    else {
        std::string msg = value_ + " " + "is already declared";
        return ErrorV(msg);
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

    std::cout << "code generation ------ " << std::endl;
    if (llvm::Value *Val = Root->codegen()) {
        // Print generated IR
        //Val->print(llvm::errs());
        //llvm::errs() << "\n";

        // Finish off the function with a return void
        Builder->CreateRetVoid();

        TheModule->print(llvm::errs(), nullptr);
    }
    else {
        fprintf(stderr, "Code generation failed.\n");
    }
}
