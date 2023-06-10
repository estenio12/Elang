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
    static const std::string UNDEFINED  = "undefined";
    static const std::string NUMBER     = "number";
    static const std::string CHARACTER  = "character";
    static const std::string BUILDING   = "building";
    static const std::string KEYWORD    = "keyword";
    static const std::string BOOLEAN    = "boolean";
    static const std::string TYPE       = "type";
    static const std::string IDENTIFIER = "identifier";
    static const std::string DELIMITER  = "delimiter";
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
    static const char EOL                 = ';';
    static const char COLON               = ':';
    static const char ASSIGN              = '=';
    static const char OPEN_PARAM          = '(';
    static const char CLOSE_PARAM         = ')';
    static const char OPEN_BRACE          = '{';
    static const char CLOSE_BRACE         = '}';
    static const char OPEN_SQUAREBRACKET  = '[';
    static const char CLOSE_SQUAREBRACKET = ']';
    static const char COMMA               = ',';
    static const char APOSTROPHE          = '\'';
    static const char QUOTATION_MARKS     = '\"';
    static const char BACK_SLASH          = '/';
    static const char _EOF                = '\0';

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
    static const std::string SHIFTRIGHT = ">>";
    static const std::string SHIFTLEFT  = "<<";
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
