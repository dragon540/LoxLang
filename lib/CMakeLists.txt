add_library(LoxLangLib STATIC Lexer.cpp)

target_include_directories(LoxLangLib PUBLIC ${CMAKE_SOURCE_DIR}/include)