# LoxLang using MLIR and LLVM

## How to build:

``` $ mdkir build```

``` $ cmake -DLLVM_DIR=path_to_llvm_build/lib/cmake/llvm -B build/```

``` $ cd build```

``` $ cmake --build .```

## First draft grammar

1. Program ->   Declaration* EOF

2. Declaration -> VarDecl
                  | Statement
                  
3. Statement -> ExprStmt
                | printStmt
                
4. ExprStmt -> Literal
               | Unary
               | Binary
               | Grouping

5. printStmt -> PRINT OPEN_PAREN ExprStmt CLOSE_PAREN SEMICOLON  
                
6. Literal -> NUMBER | STRING | "true" | "false" | "nil" ;

7. Grouping -> "(" ExprStmt ")" ;

8. Unary -> ( "-" | "!" ) ExprStmt ;

9. Binary -> ExprStmt Operator exprStmt ;

10. Operator -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;

11. VarDecl -> VAR Identifier SEMICOLON
               | VAR Identifier EQUAL ExprStmt SEMICOLON
