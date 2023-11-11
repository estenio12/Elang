// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>

enum TYPE_IDENTIFIER
{
    IDENTIFIER_VARIABLE,
    IDENTIFIER_FUNCTION,
    NOT_FOUND
};

enum TYPE_TOKEN
{
    T_KEYWORD,
    T_TYPE,
    T_IDENTIDIER,
    T_DELIMITER,
    T_ARITHMETIC,
    T_PREFIX,
    T_POSTFIX,
    T_LOGICAL,
    T_FLOAT_LITERAL,
    T_INT_LITERAL,
    T_CHAR_LITERAL,
    T_BOOL_LITERAL,
    T_STRING_LITERAL
};

namespace TEMPLATE
{
    static const std::string IS_DIGIT         = "0123456789.";
    static const std::string IS_ALPHA         = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLIMOPQRSTUVWXYZ";
    static const std::string IS_ALPHA_NUMERIC = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLIMOPQRSTUVWXYZ0123456789";
    static const std::string TRUE_LITERAL     = "true";
    static const std::string FALSE_LITERAL    = "false";
}

namespace KEYWORD
{
    static const std::string T_VAR      = "var";
    static const std::string T_CONST    = "const";
    static const std::string T_ARRAY    = "array";
    static const std::string T_FUN      = "fun";
    static const std::string T_FOR      = "for";
    static const std::string T_WHILE    = "while";
    static const std::string T_END      = "end";
    static const std::string T_IF       = "if";
    static const std::string T_ELSE     = "else";
    static const std::string T_RETURN   = "return";
    static const std::string T_BREAK    = "break";
    static const std::string T_CONTINUE = "continue";
}

namespace TYPE
{
    static const std::string T_FLOAT  = "float";
    static const std::string T_INT    = "int";
    static const std::string T_BOOL   = "bool";
    static const std::string T_CHAR   = "char";
    static const std::string T_VOID   = "void";
    static const std::string T_STRING = "string";
}

namespace DELIMITER
{
    static const std::string T_COLON         = ":";
    static const std::string T_COMMA         = ",";
    static const std::string T_OPEN_BRACKET  = "{";
    static const std::string T_CLOSE_BRACKET = "}";
    static const std::string T_OPEN_BRANCE   = "[";
    static const std::string T_CLOSE_BRACE   = "]";
    static const std::string T_OPEN_PAREM    = "(";
    static const std::string T_CLOSE_PAREM   = ")";
    static const std::string T_QUOTATION_MARKS = "\"";
    static const std::string T_APHOSTROFE      = "\'";
    static const std::string T_EOF             = ";";
    static const std::string T_ASSIGN      = "=";
}

namespace ARITHMETIC
{
    static const std::string T_PLUS        = "+";
    static const std::string T_MINUS       = "-";
    static const std::string T_DIV         = "/";
    static const std::string T_MUL         = "*";
    static const std::string T_MOD         = "%";
    static const std::string T_OR          = "|";
    static const std::string T_AND         = "&";
    static const std::string T_POW         = "^";
    static const std::string T_PLUS_EQ     = "+=";
    static const std::string T_MINUS_EQ    = "-=";
    static const std::string T_DIV_EQ      = "/=";
    static const std::string T_MUL_EQ      = "*=";
    static const std::string T_SHIFT_RIGHT = ">>";
    static const std::string T_SHIFT_LEFT  = "<<";
}

namespace SELF_INCREMENTATION
{
    static const std::string T_PLUS_PLUS   = "++";
    static const std::string T_MINUS_MINUS = "--";
}

namespace LOGICAL 
{
    static const std::string T_GREAT_THEN    = ">";
    static const std::string T_LESS_THEN     = "<";
    static const std::string T_GREAT_THEN_EQ = "<=";
    static const std::string T_LESS_THEN_EQ  = ">=";
    static const std::string T_OR            = "||";
    static const std::string T_AND           = "&&";
    static const std::string T_DIFF          = "!=";
    static const std::string T_EQUALS        = "==";
}

namespace SKIP_CHARACTER
{
    static const char WHITESPACE = ' ';
    static const char TABULATION = '\t';
    static const char RETURN     = '\r';
    static const char NEWLINE    = '\n';
}

