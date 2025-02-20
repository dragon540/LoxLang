#include "Lexer.h"

Lexer::Lexer(llvm::StringRef & codeblock) : codeblock_(codeblock) {
    llvm::outs() << "Lexing started\n";
    lex();
    llvm::outs() << "Lexing completed\n";

}

char Lexer::readNext() {
    return codeblock_[str_idx + 1];
}

char Lexer::consumeNext() {
    str_idx++;
    return codeblock_[str_idx];
}

bool Lexer::isAlpha(char c) {
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
        return true;
    }
    return false;
}

bool Lexer::isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

void Lexer::lex() {
    int state = 0;
    std::string temp = "";
    for (auto &i : codeblock_) {
        switch (state) {
        case 0:
            if (i == 'v') {
                temp += i;
                state = 1;
            }
            break;;
        case 1:
            if (i == 'a') {
                temp += i;
                state = 2;
            }
            break;
        case 2:
            if (i == 'r') {
                temp += i;
                state = 3;
            }
            break;
        case 3:
            if (i == ' ') {
                token_list.emplace_back(Token::TokenType::var_decl, temp, 1);
                temp = "";
                state = 0;
            }
            break;
        }
    }
}

void Lexer::printTokenList() {
    llvm::errs() << "Token list printing\n";
    for (auto &i : token_list) {
        llvm::outs() << "Token type: " << i.type_ << "\n";
        llvm::outs() << "Token value: " << i.value_ << "\n";
        llvm::outs() << "Lineno: " << i.lineno_ << "\n";
    }
}