// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <vector>

using Tokens_lst = std::vector<std::pair<std::string, std::string>>;

namespace TokenList
{
    static Tokens_lst Tokens;
}

namespace DEFAULT
{
    static const char LINEBREAK   = '\n';
    static const char LINECOMMENT = '/';
    static const char WHITESPACE  = ' ';
    static const char ENDOFLINE   = ';';
    static const char OPENDEFSCOPE   = '(';
    static const char CLOSEDEFSCOPE  = ')';
    static const char OPENSCOPE  = '{';
    static const char CLOSESCOPE  = '}';
}

namespace KEYWORDS
{
    static const uint8_t SIZE_DECLARATOR = 3;
    static const uint8_t SIZE_ASSIGNMENT = 5;
    static const uint8_t SIZE_LOGIC      = 9;
    static const uint8_t SIZE_DATATYPE   = 4;
    
    static const std::string digits  = "0123456789";
    static const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const std::string datatype[]
    {
        "number", "boolean", "char", "string"
    };

    static const std::string declarator[SIZE_DECLARATOR]
    {
        "var", "const", "array"
    };

    static const std::string assignment[SIZE_ASSIGNMENT]
    {
        "+", "-", "*", "/", "="
    };

    static const std::string logic[SIZE_LOGIC]
    {
        "true", "false", "!=", ">", "<", ">=", "<=",
        "==", "||"
    };
}