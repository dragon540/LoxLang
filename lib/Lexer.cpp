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

// returns current character and move to next
// character of text being read
char Lexer::consume() {
    current_idx++;
    return src_[current_idx - 1];
}

// if current character matches c, consume it
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

// called from a loop and within each turn
// of the loop, we try to scan a single token
void Lexer::scanToken() {
    char c = consume();
    switch(c) {
        case ',':
            addToken(TokenType::comma, line);
        break;
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
        case ';':
            addToken(TokenType::semicolon, line);
        break;

        case '/':
            //scan_slash();
        break;
        case '<':
            scan_less_than();
        break;
        case '>':
            scan_more_than();
        break;

        case '=':
            scan_equal();
        break;
        case '!':
            scan_not();
        break;

        case ' ':
        case '\t':
        case '\r':
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
    llvm::errs() << "Printing source code: \n" << src_ << "\n";
    llvm::errs() << "Token list printing\n";
    for (auto &i : token_list) {
        llvm::outs() << "Token type: " << static_cast<int>(i.type_) << "\n";
        if(i.value_ != "\0") {
            llvm::outs() << "Token value: " << i.value_ << "\n";
        }
        llvm::outs() << "Lineno: " << i.lineno_ << "\n";
    }
}

/**
void Lexer::scan_slash() {
    if(match('/')) {
        // ignore till endline is not consumed
        while(!match('\n')) {
            consume();
        }
        consume();
    }
    else {
        addToken(TokenType::div, line);
    }
}
**/

void Lexer::scan_less_than() {
    if(match('=')) {
        addToken(TokenType::less_than_equal, line);
    }
    else {
        addToken(TokenType::less_than, line);
    }
}

void Lexer::scan_more_than() {
    if(match('=')) {
        addToken(TokenType::more_than_equal, line);
    }
    else {
        addToken(TokenType::more_than, line);
    }
}

void Lexer::scan_equal() {
    if(match('=')) {
        addToken(TokenType::equal_comparison, line);
    }
    else {
        addToken(TokenType::equal_assignment, line);
    }
}

void Lexer::scan_not() {
    if(match('=')) {
        addToken(TokenType::not_equal_comparison, line);
    }
    else {
        addToken(TokenType::not_operator, line);
    }
}
