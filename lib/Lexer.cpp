#include "Lexer.h"

Lexer::Lexer(llvm::StringRef & src) : src_(src) {
    llvm::outs() << "Lexing started\n";
    lex();
    llvm::outs() << "Lexing completed\n";

}

bool Lexer::isEof() {
    if(current_idx < src_.size()) {
          return false;
    }
    return true;
}

char Lexer::readNext() {
    if(current_idx + 1 >= src_.size()) {
        return '\0';
    }
    return src_[current_idx + 1];
}

char Lexer::consume() {
    current_idx++;
    return src_[current_idx - 1];
}

bool Lexer::match(char c) {
    if(current_idx < src_.size()) {
        if(src_[current_idx] == c) {
            consume();
            return true;
        }
    }
    return false;
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

void Lexer::addToken(TokenType type, std::string literal, unsigned int lineno) {
    token_list.emplace_back(type, literal, lineno);
}

// function overloading for token types which does not require literal
// to be stored explicitly eg. +, -, <=, etc
void Lexer::addToken(TokenType type, unsigned int lineno) {
    token_list.emplace_back(type, lineno);
}

void Lexer::scanToken() {
    char c = consume();
    switch(c) {
        case '(':
            addToken(TokenType::open_paren, line);
        break;
        case ')':
            addToken(TokenType::close_paren, line);
        break;
        case '{':
            addToken(TokenType::open_curly, line);
        break;
        case '}':
            addToken(TokenType::close_curly, line);
        break;
        case '+':
            addToken(TokenType::plus, line);
        break;
        case '-':
            addToken(TokenType::minus, line);
        break;
        case '*':
            addToken(TokenType::mul, line);
        break;
        case ',':
            addToken(TokenType::comma, line);
        break;

        case '>':
            if(match('=')) {
                addToken(TokenType::more_than_equal, line);
            }
            else {
                addToken(TokenType::more_than, line);
            }
        break;

        case ' ':
        break;

        case '\n':
            line++;
        break;
    }
}

void Lexer::lex() {
    while(!isEof()) {
        start_idx = current_idx;
        scanToken();
    }
}

void Lexer::printTokenList() {
    llvm::errs() << "Token list printing\n";
    for (auto &i : token_list) {
        llvm::outs() << "Token type: " << static_cast<int>(i.type_) << "\n";
        if(i.value_ != "\0") {
            llvm::outs() << "Token value: " << i.value_ << "\n";
        }
        llvm::outs() << "Lineno: " << i.lineno_ << "\n";
    }
}
