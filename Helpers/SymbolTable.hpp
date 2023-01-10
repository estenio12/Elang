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

namespace LANG
{
    static const char LINEBREAK       = '\n';
    static const char LINECOMMENT     = '/';
    static const char WHITESPACE      = ' ';
    static const char ENDOFLINE       = ';';
    static const char OPENDEFSCOPE    = '(';
    static const char CLOSEDEFSCOPE   = ')';
    static const char OPENSCOPE       = '{';
    static const char CLOSESCOPE      = '}';
    static const char ARRAYOPENSCOPE  = '[';
    static const char ARRAYCLOSESCOPE = ']';
    static const char NUMBERFLOAT     = '.';
}

namespace KEYWORDS
{
    static const uint8_t SIZE_DECLARATOR = 3;
    static const uint8_t SIZE_ASSIGNMENT = 5;
    static const uint8_t SIZE_LOGIC      = 9;
    static const uint8_t SIZE_TYPE       = 4;
    
    static const std::string digits  = "0123456789";
    static const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const std::string type[SIZE_TYPE]
    {
        "number", "bool", "char", "string"
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

namespace TOOLS
{
    static bool IsNumber(char character)
    {
        for(int i = 0; i < KEYWORDS::digits.size(); i++)
        {
            if(KEYWORDS::digits[i] == character)
            {
                return true;
            }
        }

        return false;
    }

    static bool IsLetter(char character)
    {
        for(int i = 0; i < KEYWORDS::letters.size(); i++)
        {
            if(character == KEYWORDS::letters[i])
            {
                return true;
            }
        }

        return false;
    }

    static bool IsFloatNumber(char Current, char Next)
    {
        if(Current == LANG::NUMBERFLOAT)
        {
            for(int i = 0; i < KEYWORDS::digits.size(); i++)
            {
                if(KEYWORDS::digits[i] == Next)
                {
                    return true;
                }
            }
        }

        return false;
    }
}