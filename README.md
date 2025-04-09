# LoxLang using MLIR and LLVM

## How to build:

``` $ mdkir build```

``` $ cmake -DLLVM_DIR=path_to_llvm_build/lib/cmake/llvm -B build/```

``` $ cd build```

``` $ cmake --build .```

## Grammar

1. Program ->   Declaration* EOF

2. Declaration -> VarDecl
                | FuncDecl
                | ClassDecl
                | Statement
                  
3. Statement -> ExprStmt
              | ForStmt
              | IfStmt
              | PrintStmt
              | ReturnStmt
              | WhileStmtl
              | Block
                
4. ExprStmt -> Literal
             | Unary
             | Binary
             | Grouping
             
5. ForStmt -> FOR OPEN_PAREN VarDecl SEMICOLON ExprStmt SEMICOLON 
              ExprStmt CLOSE_PAREN Statement
         
6. IfStmt -> IF OPEN_PAREN ExprStmt CLOSE_PAREN Block
           | IF OPEN_PAREN ExprStmt CLOSE_PAREN Block ELSE Block

7. PrintStmt -> PRINT OPEN_PAREN ExprStmt CLOSE_PAREN SEMICOLON 

8. ReturnStmt -> RETURN SEMICOLON
               | RETURN ExprStmt SEMICOLON

9. WhileStmt -> WHILE OPEN_PAREN ExprStmt CLOSE_PAREN Block

10. Block -> OPEN_CURLY Statement* CLOSE_CURLY
                
6. Literal -> NUMBER | STRING | "true" | "false" | "nil" ;

7. Grouping -> "(" ExprStmt ")" ;

8. Unary -> ( "-" | "!" ) ExprStmt ;

9. Binary -> ExprStmt Operator ExprStmt ;

10. Operator -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;

11. VarDecl -> VAR Identifier SEMICOLON
             | VAR Identifier EQUAL ExprStmt SEMICOLON
               
12. FuncDecl -> FUN Function

13. ClassDecl -> CLASS Identifier OPEN_CURLY Function* CLOSE_CURLY SEMICOLON

14. Function -> Identifier ( );
              | Identifier ( Parameters ) Block
                
15. Parameters -> Identifier
                | Identifier , Identifier+
                
16. VAR -> "var"
17. PRINT -> "print"
18. CLASS -> "class"
19. RETURN -> "return"

