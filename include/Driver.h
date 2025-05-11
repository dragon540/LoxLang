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
        if(!val) {
            std::cout << "nullptr" << std::endl;
            return nullptr;
        }
        Builder->CreateStore(val, Alloca);
    }

    NamedValues[iden->value_] = Alloca;
    //std::cout << "var decl done" << std::endl;
    return Alloca;
}

Value* FuncDeclNode::codegen() {
}

Value* ClassDeclNode::codegen() {

}

Value* BlockNode::codegen() {
    std::cout << "Block codegen" << std::endl;
    Function *func = Builder->GetInsertBlock()->getParent();
    BasicBlock *bb = BasicBlock::Create(*TheContext, "block", func);
    Builder->SetInsertPoint(bb);
    for(auto & i : declarations) {
        //std::cout << "Inside loop" << std::endl;
        i->codegen();
    }
    //std::cout << "reached here" << std::endl;
    return bb;
}

Value* ParametersNode::codegen() {
    for(auto & i : identifiers) {
        i->codegen();
    }
}

Value* IfStmtNode::codegen() {
    //std::cout << "IfStmt codegen" << std::endl;
    Function *func = Builder->GetInsertBlock()->getParent();
    BasicBlock *entry = Builder->GetInsertBlock();

    BasicBlock *if_basic_block = (BasicBlock*)if_block->codegen();
    BasicBlock *else_basic_block = nullptr;
    if(else_block != nullptr) {
        else_basic_block = (BasicBlock*)else_block->codegen();
    }

    Builder->SetInsertPoint(entry);

    return Builder->CreateCondBr(if_expr->codegen(), if_basic_block, else_basic_block);
}

Value* ReturnStmtNode::codegen() {

}

Value* WhileStmtNode::codegen() {
    BasicBlock *entry = Builder->GetInsertBlock();

    BasicBlock *loop_exit = BasicBlock::Create(*TheContext, "loop_exit", Builder->GetInsertBlock()->getParent());
    Builder->SetInsertPoint(loop_exit);
    Builder->CreateRetVoid();

    Builder->SetInsertPoint(entry);

    BasicBlock *while_loop_block = (BasicBlock*)loop_block->codegen();
    Builder->CreateRetVoid();

    Builder->SetInsertPoint(entry);
    BasicBlock *loop_holder = BasicBlock::Create(*TheContext, "loop_holder", Builder->GetInsertBlock()->getParent());

    Builder->CreateBr(loop_holder);

    Builder->SetInsertPoint(loop_holder);

    return Builder->CreateCondBr(conditional_expr->codegen(), while_loop_block, loop_exit);
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

Value* programCodegen(std::list<DeclNode*> declarations) {
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

    for(auto &i : declarations) {
        i->codegen();
        //TheModule->print(llvm::errs(), nullptr);
    }

    // Finish off the function with a return void
    Builder->CreateRetVoid();

    TheModule->print(llvm::errs(), nullptr);
}
