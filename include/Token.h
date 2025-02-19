#pragma once

#include <string>

class  Token {
public:
	Token(int token_type, std::string &token_val, int line);
	enum TokenType {
		numeric,
		identifier,
		equal,
		open_paren,
		close_paren,
		open_curly,
		close_curly,
		plus,
		minus,
		asterisk,
		div,
		semicolon
	};
	int type;
	std::string &value;

	// for error analysis
	int lineno;
};