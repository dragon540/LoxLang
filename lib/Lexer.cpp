#include "Lexer.h"

Lexer::Lexer(llvm::StringRef & src) : src_(src) {
    llvm::outs() << "Lexing started\n";
    lex();
    llvm::outs() << "Lexing completed\n";

}

std::vector<Token> Lexer::return_token_list() {
    return token_list;
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

// returns current character
char Lexer::readCurrent() {
    return src_[current_idx];
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
            scan_slash();
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
        case '"':
            scan_quote();
        break;

        case '_':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
    {
            std::string literal = "";
            literal += c;
            scan_literal(literal);
        break;
    }
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
    {
        std::string numeric_lit = "";
        numeric_lit += c;
        // problem is here, unable to lex two digit number into single token
        if(isDigit(readCurrent())) {
            scan_numeric(numeric_lit);
        } else {
            addToken(TokenType::int_numeric, numeric_lit, line);
        }
        break;
    }

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
    TokenName tn;
    llvm::errs() << "Token list printing\n";
    for (auto &i : token_list) {
        llvm::outs() << "Token type: " << tn.tokenToNameMap.at(static_cast<int>(i.type_)) << "\n";
        if(i.value_ != "\0") {
            llvm::outs() << "Token value: " << i.value_ << "\n";
        }
        llvm::outs() << "Lineno: " << i.lineno_ << "\n";
    }
}

void Lexer::scan_slash() {
    if(match('/')) {
        // ignore till endline or eof is reached
        while( (src_[current_idx] != '\n') && !isEof() ) {
            consume();
        }
    }
    else {
        addToken(TokenType::div, line);
    }
}

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

void Lexer::scan_quote() {
    std::string literal = "";
    while( isAlpha(readNext()) ) {
        literal += consume();
    }
    literal += consume();
    if(match('"')) {
        addToken(TokenType::string_lit, literal, line);
    }
    else {
        std::cout << "expected \" missing" << std::endl;
    }
}

void Lexer::scan_literal(std::string literal) {
    //start_idx = current_idx - 1;
    while( isAlpha(readNext()) ) {
        literal += consume();
    }
    literal += consume();
    scan_kw_and_identifier(literal);
}

void Lexer::scan_numeric(std::string numeric_literal) {
    while( isDigit(readCurrent()) ) {
        numeric_literal += consume();
    }
    //numeric_literal += consume();
    addToken(TokenType::int_numeric, numeric_literal, line);
}

void Lexer::scan_kw_and_identifier(std::string literal) {
    if(literal == "var") {
        addToken(TokenType::var_kw, line);
    }
    else if(literal == "func") {
        addToken(TokenType::func_kw, line);
    }
    else if(literal == "if") {
        addToken(TokenType::if_kw, line);
    }
    else if(literal == "elif") {
        addToken(TokenType::elif_kw, line);
    }
    else if(literal == "else") {
        addToken(TokenType::else_kw, line);
    }
    else if(literal == "for") {
        addToken(TokenType::for_kw, line);
    }
    else if(literal == "while") {
        addToken(TokenType::while_kw, line);
    }
    else if(literal == "true") {
        addToken(TokenType::true_kw, line);
    }
    else if(literal == "false") {
        addToken(TokenType::false_kw, line);
    }
    else if(literal == "print") {
        addToken(TokenType::print_kw, line);
    }
    else if(literal == "class") {
        addToken(TokenType::class_kw, line);
    }
    else if(literal == "return") {
        addToken(TokenType::return_kw, line);
    }
    else {
        addToken(TokenType::identifier, literal, line);
    }
}
