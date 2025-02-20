#pragma once

#include <string>
#include "llvm/Support/raw_ostream.h"

class  Token {
public:
	Token(int token_type, std::string & token_val, int lineno) :
		type_(token_type), value_(token_val), lineno_(lineno) {}

	enum TokenType {
		var_decl,
		func_decl,
		identifier,
		equal_assignment, // =
		numeric,
		open_paren,
		comma,
		close_paren,
		open_curly,
		close_curly,
		conditional_if,
		conditional_elif,
		conditional_else,
		for_loop,
		plus,
		minus,
		mul,
		div,
		less_than,
		more_than,
		less_than_equal,
		more_than_equal,
		equal_comparison, // ==
		semicolon,
		bool_true_dtype,
		bool_false_dtype,
		int_dtype,
		dec_dtype,
		string_dtype,
		nil_dtype
	};
	int type_;
	std::string value_;

	// for error analysis
	int lineno_;
};