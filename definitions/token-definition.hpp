// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>

enum TOKEN_DEF
{
    KEYWORD,
    TYPE,
    IDENTIDIER,
    DELIMITER,
    ARITHMETIC,
    PREFIX,
    POSTFIX,
    LOGICAL,
    FLOAT_LITERAL,
    INT_LITERAL,
    CHAR_LITERAL,
    BOOL_LITERAL
};

namespace TOKEN 
{
    static const std::string IS_DIGIT = "0123456789.";
    static const std::string IS_ALPHA = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLIMOPQRSTUVWXYZ_";

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

namespace SKIP_CHARACTER
{
    static const char WHITESPACE = ' ';
    static const char TABULATION = '\t';
    static const char RETURN     = '\r';
    static const char NEWLINE    = '\n';
}

