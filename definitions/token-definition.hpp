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

static const std::string KEYWORD[] 
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

static const std::string TYPE[] 
{
    "float",
    "int",
    "bool",
    "char",
    "void"
};

static const std::string DELIMITER[] 
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

static const std::string ARITHMETIC[] 
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

static const std::string PREFIX[] 
{
    "++",
    "--"
};

static const std::string POSTFIX[] 
{
    "++",
    "--"
};

static const char SKIP_CHARACTER[] 
{
    ' '
};

static const std::string LOGICAL[] 
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



