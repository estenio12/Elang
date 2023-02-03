// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <vector>

using Dictionary = std::pair<std::string, std::string>;
using Tokens_lst = std::vector<std::pair<std::string, std::string>>;

namespace LANG
{
    static const char LINEBREAK       = '\n';
    static const char LINECOMMENT     = '/';
    static const char WHITESPACE      = ' ';
    static const char CHARSTMT        = '\'';

    static const int SIZE_STMT        = 12;
    
    static const std::string STMT[SIZE_STMT]
    {
        ";","(",")","{","}","[","]",".",":","_","0",","
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
        "undefined",
        "separate",
    };

    static const int ENDOFLINE  = 0;
    static const int OPENPAREM  = 1;
    static const int CLOSEPAREM = 2;
    static const int OPENBRACE  = 3;
    static const int CLOSEBRACE = 4;
    static const int OPENBRACKET    = 5;
    static const int CLOSEBRACKET   = 6;
    static const int DOT            = 7;
    static const int TYPEASSIGNMENT = 8;
    static const int UNDERLINE      = 9;
    static const int UNDEFINED      = 10;
    static const int SEPARATE       = 10;
};

namespace NAMES
{
    static const std::string DECLARATOR = "declarator";
    static const std::string NUMBER     = "number";
    static const std::string IDENTIFIER = "identifier";
    static const std::string TYPE       = "type";
    static const std::string ASSIGNMENT = "assignment";
    static const std::string RELATIONAL = "relacional";
    static const std::string LOGICAL    = "logical";
    static const std::string VALUE      = "value";
    static const std::string CHARACTER  = "character";
};


namespace KEYWORDS
{
    static const int SIZE_DECLARATOR = 3;
    static const int SIZE_ASSIGNMENT = 5;
    static const int SIZE_RELATIONAL = 6;
    static const int SIZE_LOGICAL    = 2;
    static const int SIZE_TYPE       = 3;
    static const int SIZE_VALUE      = 3;
    
    static const std::string Digits  = "0123456789";
    static const std::string Letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const int ASSIGN = 4;

    static const std::string Type[]
    {
        "number", "bool", "char"
    };

    static const std::string Declarator[]
    {
        "var", "const"
    };

    static const std::string Assignment[]
    {
        "+", "-", "*", "/", "="
    };

    static const std::string Relational[]
    {
        "!=", ">", "<", ">=", "<=", "=="
    };

    static const std::string Logical[]
    {
        "&&", "||"
    };

    static const std::string VALUE[]
    {
        "true", "false", "null"
    };

    // static const std::string null = "null";

    enum EDeclarator
    {
        VAR = 0,
        CONST
    };

    enum EType
    {
        NUMBER = 0,
        BOOL,
        CHAR
    };

    enum EAssignment
    {
        PLUS,
        LESS,
        MUL,
        DIV,
        ASSIGNMENT
    };

    enum EValues
    {
        TRUE = 0,
        FALSE,
        PNULL
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
        if(Current == LANG::STMT[7][0])
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
