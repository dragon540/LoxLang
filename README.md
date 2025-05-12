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
              | AssignStmt
              | ForStmt
              | IfStmt
              | PrintStmt
              | ReturnStmt
              | WhileStmtl
              | Block
                
4. ExprStmt -> Literal
             | Identifier
             | Unary
             | Binary
             | Grouping
             
5. AssignStmt -> Identifier EQUAL ExprStmt SEMICOLON
             
6. ForStmt -> FOR OPEN_PAREN VarDecl SEMICOLON ExprStmt SEMICOLON 
              ExprStmt CLOSE_PAREN Block
         
7. IfStmt -> IF OPEN_PAREN ExprStmt CLOSE_PAREN Block
           | IF OPEN_PAREN ExprStmt CLOSE_PAREN Block ELSE Block

8. PrintStmt -> PRINT OPEN_PAREN ExprStmt CLOSE_PAREN SEMICOLON 

9. ReturnStmt -> RETURN SEMICOLON
               | RETURN ExprStmt SEMICOLON

10. WhileStmt -> WHILE OPEN_PAREN ExprStmt CLOSE_PAREN Block

11. Block -> OPEN_CURLY Statement* CLOSE_CURLY
                
12. Literal -> NUMBER | STRING | "true" | "false" | "nil" ;

13. Grouping -> "(" ExprStmt ")" ;

14. Unary -> ( "-" | "!" ) ExprStmt ;

15. Binary -> ExprStmt Operator ExprStmt ;

16. Operator -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;

17. VarDecl -> VAR Identifier SEMICOLON
             | VAR Identifier EQUAL ExprStmt SEMICOLON
               
18. FuncDecl -> FUN Function

19. ClassDecl -> CLASS Identifier OPEN_CURLY Function* CLOSE_CURLY SEMICOLON

20. Function -> Identifier ( ) Block;
              | Identifier ( Parameters ) Block
                
21. Parameters -> Identifier
                | Identifier , Identifier+
                
22. VAR -> "var"
23. PRINT -> "print"
24. CLASS -> "class"
25. RETURN -> "return"

