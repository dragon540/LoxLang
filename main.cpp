#include <iostream>
#include "Lexer.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    llvm::StringRef str2("+ - * +, \n>= \n> == var func hello \nworld = != \n ! \n\n\n\n \n != // + *\n >=");
	Lexer l(str2);
	l.printTokenList();
	return 0;
}
