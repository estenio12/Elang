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

    static const int SIZE_STMT        = 11;
    
    static const char STMT[SIZE_STMT]
    {
        ';','(',')','{','}','[',']','.',':','_','0'
    };

    static const std::string STMTNAME[]
    {
        "endofline",
        "openparam",
        "closeparam",
        "openbrace",
        "closebrace",
        "openbracket",
        "closebracket",
        "dot",
        "typeassignment",
        "underline",
        "undefined"
    };
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

    static const std::string Type[]
    {
        "number", "bool", "char"
    };

    static const std::string Declarator[]
    {
        "var", "const", "array"
    };

    static const std::string Assignment[]
    {
        "+", "-", "*", "/", "="
    };

    static const std::string Relational[]
    {
        "true", "false", "!=", ">", "<", ">=", "<=",
        "=="
    };

    static const std::string Logic[]
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
        if(Current == LANG::STMT[7])
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
    static const std::string TYPE       = "type";
};