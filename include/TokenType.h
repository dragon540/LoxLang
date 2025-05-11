#pragma once

#include <map>

enum class TokenType {
    // keyword
    var_kw,
    func_kw,
    class_kw,
    if_kw,
    elif_kw,
    else_kw,
    for_kw,
    while_kw,
    true_kw,
    false_kw,
    print_kw,
    return_kw,

    //
    identifier,
    int_numeric,
    decimal_numeric,
    string_lit,
    nil,

    // single character lexeme
    comma,
    open_paren,
    close_paren,
    open_curly,
    close_curly,
    plus,
    minus,
    mul,
    semicolon,

    //
    div,
    less_than,
    less_than_equal,
    more_than,
    more_than_equal,
    equal_assignment, // =
    equal_comparison, // ==
    not_operator,
    not_equal_comparison,

    // end-of-file
    eof
};

class TokenName{
public:
    std::map<int, std::string> tokenToNameMap;

    TokenName() {
        tokenToNameMap.insert({static_cast<int>(TokenType::var_kw), "var_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::func_kw), "func_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::class_kw), "class_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::if_kw), "if_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::elif_kw), "elif_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::else_kw), "else_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::for_kw), "for_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::while_kw), "while_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::true_kw), "true_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::false_kw), "false_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::print_kw), "print_kw"});
        tokenToNameMap.insert({static_cast<int>(TokenType::return_kw), "return_kw"});

        tokenToNameMap.insert({static_cast<int>(TokenType::identifier), "identifier"});
        tokenToNameMap.insert({static_cast<int>(TokenType::int_numeric), "int_numeric"});
        tokenToNameMap.insert({static_cast<int>(TokenType::decimal_numeric), "decimal_numeric"});
        tokenToNameMap.insert({static_cast<int>(TokenType::string_lit), "string_lit"});
        tokenToNameMap.insert({static_cast<int>(TokenType::nil), "nil"});

        tokenToNameMap.insert({static_cast<int>(TokenType::comma), "comma"});
        tokenToNameMap.insert({static_cast<int>(TokenType::open_paren), "open_paren"});
        tokenToNameMap.insert({static_cast<int>(TokenType::close_paren), "close_paren"});
        tokenToNameMap.insert({static_cast<int>(TokenType::open_curly), "open_curly"});
        tokenToNameMap.insert({static_cast<int>(TokenType::close_curly), "close_curly"});
        tokenToNameMap.insert({static_cast<int>(TokenType::plus), "plus"});
        tokenToNameMap.insert({static_cast<int>(TokenType::minus), "minus"});
        tokenToNameMap.insert({static_cast<int>(TokenType::mul), "mul"});
        tokenToNameMap.insert({static_cast<int>(TokenType::semicolon), "semicolon"});

        tokenToNameMap.insert({static_cast<int>(TokenType::div), "div"});
        tokenToNameMap.insert({static_cast<int>(TokenType::less_than), "less_than"});
        tokenToNameMap.insert({static_cast<int>(TokenType::less_than_equal), "less_than_equal"});
        tokenToNameMap.insert({static_cast<int>(TokenType::more_than), "more_than"});
        tokenToNameMap.insert({static_cast<int>(TokenType::more_than_equal), "more_than_equal"});
        tokenToNameMap.insert({static_cast<int>(TokenType::equal_assignment), "equal_assignment"});
        tokenToNameMap.insert({static_cast<int>(TokenType::equal_comparison), "equal_comparison"});
        tokenToNameMap.insert({static_cast<int>(TokenType::not_operator), "not_operator"});
        tokenToNameMap.insert({static_cast<int>(TokenType::not_equal_comparison), "not_equal_comparison"});

        tokenToNameMap.insert({static_cast<int>(TokenType::eof), "eof"});
    }
};
