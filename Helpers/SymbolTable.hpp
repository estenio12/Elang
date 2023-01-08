// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>

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
    static const uint8_t SIZE_DECLARATOR = 2;
    static const uint8_t SIZE_ASSIGNMENT = 5;
    static const uint8_t SIZE_LOGIC      = 9;
    
    static const std::string digits  = "0123456789";
    static const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const std::string declarator[SIZE_DECLARATOR]
    {
        "var", "const"
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