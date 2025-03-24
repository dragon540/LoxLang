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

    std::vector<Token> return_token_list();

    bool isEof();
    char readNext();

    // returns current character and move to next
    // character of text being read
    char consume();

    // if current character matches c, consume it
    bool match(char c);

	bool isAlpha(char c);
	bool isDigit(char c);
    void addToken(TokenType type, std::string literal, unsigned int lineno);
    void addToken(TokenType type, unsigned int lineno);

    // within each turn of the loop in this function,
    // we try to scan a single token
    void scanToken();

	void lex();
	void printTokenList();

private:
	llvm::StringRef src_;
    unsigned int start_idx = 0;
    unsigned int current_idx = 0;
    unsigned int line = 1;

    // scans if symbol is / and ignores if it's comment(//)
    void scan_slash();

    // scans if token is < or <=
    void scan_less_than();

    // scans if token is > or >=
    void scan_more_than();

    // scans if token is = or ==
    void scan_equal();

    // scans if token is ! or !=
    void scan_not();

    // scans if token is "
    void scan_quote();

    void scan_literal(std::string literal);

    void scan_kw_and_identifier(std::string literal);
};
