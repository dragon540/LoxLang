#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Driver.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    llvm::StringRef str2(" - \"hhh\" - \"what\" EOF");
	Lexer l(str2);
	l.printTokenList();
    Parser parser(l.return_token_list());
    std::list<StmtNode*> statements = parser.parse();
    std::cout << "here" << std::endl;
    std::cout << statements.size() << std::endl;

    for(auto & i : statements) {
        GenerateCode(i);
    }
	return 0;
}
