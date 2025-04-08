# LoxLang using MLIR and LLVM

## How to build:

``` $ mdkir build```

``` $ cmake -DLLVM_DIR=path_to_llvm_build/lib/cmake/llvm -B build/```

``` $ cd build```

``` $ cmake --build .```

## First draft grammar

1. Program -> Statement* EOF

2. Statement -> ExprStmt
                | printStmt
                
3. ExprStmt -> Literal
               | Unary
               | Binary
               | Grouping

4. printStmt -> "print" OPEN_PAREN ExprStmt CLOSE_PAREN SEMICOLON  
                
5. Literal -> NUMBER | STRING | "true" | "false" | "nil" ;

6. Grouping -> "(" ExprStmt ")" ;

7. Unary -> ( "-" | "!" ) ExprStmt ;

8. Binary -> ExprStmt Operator exprStmt ;

9. Operator -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;
