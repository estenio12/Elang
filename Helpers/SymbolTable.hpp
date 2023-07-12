// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <vector>

namespace NAME
{
    static const std::string UNDEFINED   = "undefined";
    static const std::string BUILDING    = "building";
    static const std::string KEYWORD     = "keyword";
    static const std::string NUMBER      = "number";
    static const std::string CHARACTER   = "character";
    static const std::string BOOLEAN     = "boolean";
    static const std::string STRING      = "string";
    static const std::string TVOID       = "void";
    static const std::string TYPE        = "type";
    static const std::string IDENTIFIER  = "identifier";
    static const std::string DELIMITER   = "delimiter";
    static const std::string ARITHMETIC  = "arithmatic";
    static const std::string COMPARISON  = "comparison";
    static const std::string LOGICAL     = "logical";
    static const std::string ATTRIBUTION = "attribution";
    static const std::string EXPRESSION  = "expression";
}

namespace KEYWORDS
{
    static const std::string TVAR      = "var";
    static const std::string TCONST    = "const";
    static const std::string TFUN      = "fun";
    static const std::string TRETURN   = "return";
    static const std::string TBREAK    = "break";
    static const std::string TCONTINUE = "continue";
    static const std::string TIF       = "if";
    static const std::string TELIIF    = "elif";
    static const std::string TELSE     = "else";
    static const std::string TFOR      = "for";
    static const std::string TFOREACH  = "foreach";
    static const std::string TWHILE    = "while";
    static const std::string TDO       = "do";
    static const std::string TIN       = "in";
    static const std::string TAT       = "at";
    static const std::string TEND      = "end";
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
    static const char COMMENTARY          = '#';

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
    
    static const uint8_t TNUMBER = 0;
    static const uint8_t TCHAR   = 1;
    static const uint8_t TVOID   = 2;
    static const uint8_t TBOOL   = 3;
    static const uint8_t TTEXT   = 4;
}

namespace BOOLEAN_VALUE
{
    static const std::string TTRUE  = "true";
    static const std::string TFALSE = "false";
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
    static const char SYMBOL = '=';
}

namespace LOGICAL
{
    static const std::string AND = "&&";
    static const std::string OR  = "||";
}

namespace ATTRIBUTION
{
    static const std::string INCREMENT = "++";
    static const std::string DECREMENT = "--";
}



