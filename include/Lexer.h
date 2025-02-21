#pragma once

#include <iostream>

#include "TokenType.h"
#include "Token.h"

#include <vector>
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

class Lexer {
public:
	Lexer(llvm::StringRef & src);
	std::vector<Token> token_list;

    bool isEof();
    char readNext();
    char consume();
    bool match(char c);
	bool isAlpha(char c);
	bool isDigit(char c);
    void addToken(TokenType type, std::string literal, unsigned int lineno);
    void addToken(TokenType type, unsigned int lineno);
    void scanToken();
	void lex();
	void printTokenList();

private:
	llvm::StringRef src_;
    unsigned int start_idx = 0;
    unsigned int current_idx = 0;
    unsigned int line = 1;
};
