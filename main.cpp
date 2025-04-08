#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Driver.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    //llvm::StringRef str2("var id = \"hello\" ; EOF");
    llvm::StringRef str2("var ident = 55 ;");
	Lexer l(str2);
	l.printTokenList();
    Parser parser(l.return_token_list());
    std::list<DeclNode*> declarations = parser.parse();
    std::cout << declarations.size() << std::endl;

    for(auto & i : declarations) {
        GenerateCode(i);
    }
	return 0;
}
