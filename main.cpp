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
        llvm::errs() << "Printing source code: \n" << src << "\n";

        // Lexing
        llvm::StringRef source_code(src);
        Lexer lexer(source_code);
        // Parsing
        Parser parser(lexer.return_token_list());
        std::list<DeclNode*> declarations = parser.parse();

        if(argc > 2 && strcmp(argv[2], "--lexer") == 0) {
            // Printing tokens
            lexer.printTokenList();
        }

        if(argc > 2 && strcmp(argv[2], "--ast") == 0) {
            // Pretty printer
            NodePrinter np;
                for(auto & i : declarations) {
                np.printDeclaration(i);
            }
            std::cout << std::endl;
        }
        else if(argc == 2) {
            std::cout << "Code-generation" << std::endl;
            programCodegen(declarations);

            /***
            // LLVM IR printing
            for(auto &i : declarations) {
                GenerateCode(i);
            }***/
        }
    }
    else {
        std::cerr << "Source code not given" << std::endl;
    }
	return 0;
}
