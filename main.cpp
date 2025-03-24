#include <iostream>
#include "Lexer.h"
#include "Parser.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    llvm::StringRef str2("- \"hello\" ");
	Lexer l(str2);
	l.printTokenList();
    Parser parser(l.return_token_list());
    parser.parse();
	return 0;
}
