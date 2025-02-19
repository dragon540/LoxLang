#pragma once

#include <iostream>

#include "Token.h"

#include <vector>

class Lexer {
public:
	Lexer(std::string filepath);
	std::vector<Token> token_list;

	char readNext();
	bool isEof();
	void consumeNext();
	void lex();
};
