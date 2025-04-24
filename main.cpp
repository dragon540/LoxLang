#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Driver.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"

#include <fstream>
#include <string>

int main(int argc, char **argv) {
    if(argc > 1) {
        std::string filename(argv[1]);
        std::ifstream file;
        file.open(filename);
        std::string line;
        std::string src = "";
        while(std::getline(file, line)) {
            src += line;
            src += "\n";
        }
        // std::cout << src << std::endl;
        llvm::StringRef source_code(src);
        Lexer lexer(source_code);
        lexer.printTokenList();
    }
    //llvm::StringRef str2("var id = \"hello\" ; EOF");
    /***llvm::StringRef str2("var ss = 34;");
	Lexer l(str2);
	l.printTokenList();
    Parser parser(l.return_token_list());
    std::list<DeclNode*> declarations = parser.parse();
    std::cout << declarations.size() << std::endl;

    for(auto & i : declarations) {
        GenerateCode(i);
    }***/
	return 0;
}
