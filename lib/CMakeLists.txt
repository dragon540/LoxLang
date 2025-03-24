add_library(LoxLangLib STATIC Lexer.cpp
    Parser.cpp
    NodePrinter.cpp
)

target_include_directories(LoxLangLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
