// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>
#include <vector>

namespace NAME
{
    static const std::string UNDEFINED = "undefined";
    static const std::string NUMBER    = "number";
}

namespace KEYWORDS
{
    static const std::string VAR      = "var";
    static const std::string CONST    = "const";
    static const std::string FUN      = "fun";
    static const std::string RETURN   = "return";
    static const std::string BREAK    = "break";
    static const std::string CONTINUE = "continue";
}

namespace DELIMITERS
{
    static const std::string EOL                 = ";";
    static const std::string OPEN_PARAM          = "(";
    static const std::string CLOSE_PARAM         = ")";
    static const std::string OPEN_BRACE          = "{";
    static const std::string CLOSE_BRACE         = "}";
    static const std::string OPEN_SQUAREBRACKET  = "[";
    static const std::string CLOSE_SQUAREBRACKET = "]";
    static const std::string COMMA               = ",";
    static const std::string APOSTROPHE          = "\'";
    static const std::string QUOTATION_MARKS     = "\"";
    static const std::string BACK_SLASH          = "/";
    static const char _EOF                       = '\0';

    static const char SKIP_CHAR[] = {' ', '\n', '\b', '\t'};
}

namespace DIGIT
{
    static const std::string DIGIT = ".0123456789";
}

namespace ALPHA
{
    static const std::string ALPHA        = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string ALPHANUMERIC = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
}

namespace TYPE
{
    static const std::vector<std::string> NAME {"number", "char", "void", "bool", "text" };
    
    static const uint8_t NUMBER = 0;
    static const uint8_t CHAR   = 1;
    static const uint8_t VOID   = 2;
    static const uint8_t BOOL   = 3;
    static const uint8_t TEXT   = 4;
}

namespace BOOLEAN_VALUE
{
    static const std::string TRUE  = "true";
    static const std::string FALSE = "false";
}

namespace ARITHMETIC
{
    static const std::string ADD = "+";
    static const std::string SUB = "-";
    static const std::string DIV = "/";
    static const std::string MUL = "*";
    static const std::string MOD = "%";
    static const std::string AND = "&";
    static const std::string OR  = "|";
    static const std::string SHRIGHT = ">>";
    static const std::string SHLEFT  = "<<";
}

namespace COMPARISON
{
    static const std::string DIFF    = "!=";
    static const std::string EQUALS  = "==";
    static const std::string GREAT   = ">";
    static const std::string LESS    = "<";
    static const std::string GREATEQ = ">=";
    static const std::string LESSEQ  = "<=";
}

namespace LOGICAL
{
    static const std::string AND = "&&";
    static const std::string OR  = "||";
}

namespace PREFIX
{
    static const std::string INCREMENT = "++";
    static const std::string DECREMENT = "--";
}

namespace POSFIX
{
    static const std::string INCREMENT = "++";
    static const std::string DECREMENT = "--";
}
