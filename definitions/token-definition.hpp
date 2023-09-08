///////////////////////////
// @author: Estenio Garcia
// @license: Apache 2.0
// @copyright: all
///////////////////////////

#pragma once

#include <string>

enum TOKEN_TYPE
{
    KEYWORD,
    TYPE,
    IDENTIDIER,
    DELIMITER,
    ARITHMETIC,
    PREFIX,
    POSTFIX,
    LOGICAL
};

namespace TOKEN 
{
    static const std::string KEYWORD[12] 
    {
        "var",
        "const",
        "array",
        "fun",
        "for",
        "while",
        "end",
        "if",
        "else",
        "return",
        "break",
        "continue"
    };

    static const std::string TYPE[5] 
    {
        "float",
        "int",
        "bool",
        "char",
        "void"
    };

    static const std::string DELIMITER[11] 
    {
        ":",
        ",",
        "{",
        "}",
        "[",
        "]",
        "(",
        ")",
        "\"",
        "\'",
        "="
    };

    static const std::string ARITHMETIC[14] 
    {
        "+",
        "-",
        "/",
        "*",
        "%",
        "+=",
        "-=",
        "/=",
        "*=",
        "|",
        "^",
        "&",
        ">>",
        "<<"
    };

    static const std::string PREFIX[2] 
    {
        "++",
        "--"
    };

    static const std::string POSTFIX[2] 
    {
        "++",
        "--"
    };

    static const char SKIP_CHARACTER[1] 
    {
        ' '
    };

    static const std::string LOGICAL[8] 
    {
        ">",
        "<",
        "<=",
        ">=",
        "||",
        "&&",
        "!=",
        "=="
    };
}


