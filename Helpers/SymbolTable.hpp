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

namespace KEYWORDS
{
    static const std::string DIGIT                     = "digit";
    static const std::string ALPHA                     = "alpha";
    static const std::string IDENTIFIER                = "identifier";
    static const std::string TYPE                      = "type";
    static const std::string VALUE                     = "value";
    static const std::string VARIABLE_DECARATION       = "variable-declaration";
    static const std::string FUNCTION_DECARATION       = "function-declaration";
    static const std::string PARAMETER_LIST            = "parameter-list";
    static const std::string COMPOUD_STATEMENT         = "compound-statement";
    static const std::string CALL_FUNCTION             = "call-function";
    static const std::string ARGUMENT_LIST             = "argument-list";
    static const std::string JUMP_STATEMENT            = "jump-statement";
    static const std::string CAST_EXPRESSION           = "cast-expression";
    static const std::string ADDITIVE_EXPRESSION       = "additive-expression";
    static const std::string MULTIPLICATIVE_EXPRESSION = "multiplicative-expression";
    static const std::string EXPRESSION                = "expression";
    static const std::string SELECTION_STATEMENT       = "selection-statement";
    static const std::string LOGICAL_EXPRESSION        = "logical-expression";
    static const std::string LOOP_STATEMENT            = "loop-statement";
    static const std::string SYSTEM_CALL               = "system-call";
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
    static const std::string WHITESPACE          = " ";
    static const std::string NEWLINE             = "\n";
    static const std::string RETURNING           = "\b";
    static const std::string TABULATION          = "\b";
}

namespace DIGIT
{
    static const std::string DIGIT = "0123456789";
}

namespace ALPHA
{
    static const std::string ALPHA        = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string ALPHANUMERIC = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
}

namespace TYPE
{
    static const std::vector<std::string> TYPE {"number", "letter", "word", "void", "bool" };
    
    static const uint8_t NUMBER = 0;
    static const uint8_t LETTER = 1;
    static const uint8_t WORD   = 2;
    static const uint8_t VOID   = 3;
    static const uint8_t BOOL   = 4;
}

namespace VALUE
{
    static const std::string TRUE  = "true";
    static const std::string FALSE = "false";
}



