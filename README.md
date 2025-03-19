# LoxLang using MLIR and LLVM

## How to build:

``` $ mdkir build```

``` $ cmake -DLLVM_DIR=path_to_llvm_build/lib/cmake/llvm -B build/```

``` $ cd build```

``` $ cmake --build .```

## First draft grammar

1. Expression -> Literal
                | Unary
                | Binary
                | Grouping
                
2. Literal -> NUMBER | STRING | "true" | "false" | "nil" ;

3. Grouping -> "(" Expression ")" ;

4. Unary -> ( "-" | "!" ) Expression ;

5. Binary -> Expression Operator Expression ;

6. Operator -> "==" | "!=" | "<" | "<=" | ">" | ">=" | "+" | "-" | "*" | "/" ;
