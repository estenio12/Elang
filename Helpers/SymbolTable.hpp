// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <vector>

using Tokens_lst = std::vector<std::pair<std::string, std::string>>;

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
    static const char TYPEASSIGNMENT  = ':';
    static const char UNDERLINE       = '_';
    static const char UNDEFINED       = '0';
};

namespace KEYWORDS
{
    static const int SIZE_DECLARATOR = 3;
    static const int SIZE_ASSIGNMENT = 5;
    static const int SIZE_RELATIONAL = 9;
    static const int SIZE_LOGIC      = 2;
    static const int SIZE_TYPE       = 3;
    
    static const std::string Digits  = "0123456789";
    static const std::string Letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const std::string type[]
    {
        "number", "bool", "char"
    };

    static const std::string declarator[]
    {
        "var", "const", "array"
    };

    static const std::string assignment[]
    {
        "+", "-", "*", "/", "="
    };

    static const std::string relational[]
    {
        "true", "false", "!=", ">", "<", ">=", "<=",
        "=="
    };

    static const std::string logic[]
    {
        "&&", "||"
    };
};

namespace TOOLS
{
    static bool IsNumber(char character)
    {
        for(int i = 0; i < KEYWORDS::Digits.size(); i++)
        {
            if(KEYWORDS::Digits[i] == character)
            {
                return true;
            }
        }

        return false;
    }

    static bool IsLetter(char character)
    {
        for(int i = 0; i < KEYWORDS::Letters.size(); i++)
        {
            if(character == KEYWORDS::Letters[i])
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
            for(int i = 0; i < KEYWORDS::Digits.size(); i++)
            {
                if(KEYWORDS::Digits[i] == Next)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

namespace NAMES
{
    static const std::string DECLARATOR = "declarator";
    static const std::string NUMBER     = "number";
    static const std::string IDENTIFIER = "identifier";
};