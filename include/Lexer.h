#pragma once

#include <iostream>

#include "Token.h"

#include <vector>
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

class Lexer {
public:
	Lexer(llvm::StringRef & codeblock);
	std::vector<Token> token_list;

	char readNext();
	char consumeNext();
	bool isAlpha(char c);
	bool isDigit(char c);
	void lex();
	void printTokenList();
private:
	llvm::StringRef codeblock_;
	int str_idx = 0;
};
