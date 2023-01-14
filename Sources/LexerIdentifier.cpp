#include "../Includes/Lexer.hpp"

bool Lexer::IsRelational(std::string& Token)
{
    for(int i = 0; i < KEYWORDS::SIZE_RELATIONAL; i++)
    {
        if(KEYWORDS::Relational[i] == Token)
        {
            return true;
        }
    }

    return false;
}

bool Lexer::IsAssignment(std::string& Token)
{
    for(int i = 0; i < KEYWORDS::SIZE_ASSIGNMENT; i++)
    {
        if(KEYWORDS::Assignment[i] == Token)
        {
            return true;
        }
    }

    return false;
}

bool Lexer::IsDeclarator(std::string& Token)
{
    for(int i = 0; i < KEYWORDS::SIZE_DECLARATOR; i++)
    {
        if(KEYWORDS::Declarator[i] == Token)
        {
            return true;
        }
    }

    return false;
}


bool Lexer::IsNumber(std::string& Token)
{
    for(int i = 0; i < Token.size(); i++)
    {
        if(!TOOLS::IsNumber(Token[i]))
        {
            if(TOOLS::IsFloatNumber(Token[i], Token[i + 1]))
            {
                continue;
            }

            return false;
        }

    }

    return true;
}

bool Lexer::IsValidIdentifier(std::string& Token)
{
    if(TOOLS::IsNumber(Token[0]))
    {   
        Console::PrintError("The first letter of variable name, cannot be a number! | " + Token);
        return false;
    }

    return true;
}

bool Lexer::IsType(std::string& Token)
{
    for(int i = 0; i < KEYWORDS::SIZE_TYPE; i++)
    {
        if(KEYWORDS::Type[i] == Token)
        {
            return true;
        }
    }

    return false;
}

