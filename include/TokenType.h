#pragma once

enum class TokenType {
    // keyword
    var_kw,
    func_kw,
    if_kw,
    elif_kw,
    else_kw,
    for_kw,
    true_kw,
    false_kw,
    print_kw,

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
