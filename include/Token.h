#pragma once

#include <string>

#include "TokenType.h"
#include "llvm/Support/raw_ostream.h"

class  Token {
public:
    Token(TokenType token_type, std::string & token_val, unsigned int lineno) :
		type_(token_type), value_(token_val), lineno_(lineno) {}

    Token(TokenType token_type, unsigned int lineno) :
        type_(token_type), value_("\0"), lineno_(lineno) {}


    TokenType type_;
    std::string value_;

	// for error analysis
    unsigned int lineno_;
};
