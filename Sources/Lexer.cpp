#include "../Includes/Lexer.hpp"

Lexer::Lexer(){}

Lexer::~Lexer(){}

void Lexer::Tokenaze(const std::string line)
{
    Tokens_lst Tokens;

    std::string CurrentWord;
    std::string CurrentDigit;

    for(int i = 0; i < line.size(); i++)
    {
        if(TOOLS::IsLetter(line[i]))
        {
            CurrentWord.push_back(line[i]);
        }
        else
        {
            // # Send word builded to identify
            this->IdentifyToken(CurrentWord, &Tokens);
            CurrentWord.clear();

            if(line[i] != LANG::WHITESPACE)
            {
                if(TOOLS::IsNumber(line[i]))
                {
                    CurrentDigit.push_back(line[i]);
                }
                else if(TOOLS::IsFloatNumber(line[i], line[i + 1]))
                {
                    CurrentDigit.push_back(line[i]);
                }
                else
                {
                    if(!CurrentDigit.empty())
                    {
                        this->IdentifyToken(CurrentDigit, &Tokens);
                        CurrentDigit.clear();
                    }

                    this->IdentifySpecialChar(line[i], &Tokens);
                }
            }
        }
        
    }

    // return nullptr;
}

bool Lexer::IdentifyToken(std::string Token, Tokens_lst* Tokens)
{
    if(Token.size() > 0)
    {
        // # Check if is declarator
        if(this->IsDeclarator(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::DECLARATOR, Token)
            );

            std::cout << "Debug Token: ";
            std::cout << NAMES::DECLARATOR;
            std::cout << " | " << Token;
            std::cout << std::endl;

            return true;
        }
        
        if(this->IsNumber(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::DECLARATOR, Token)
            );

            std::cout << "Debug Token: ";
            std::cout << NAMES::NUMBER;
            std::cout << " | " << Token;
            std::cout << std::endl;

            return true;
        }

        if(this->IsValidIdentifier(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::IDENTIFIER, Token)
            );

            std::cout << "Debug Token: ";
            std::cout << NAMES::IDENTIFIER;
            std::cout << " | " << Token;
            std::cout << std::endl;

            return true;
        }

        // # Not recognize token
        Console::PrintError("unrecognized token | " + Token);
    }

    return false;
}

bool Lexer::IdentifySpecialChar(const char Token, Tokens_lst* Tokens)
{
    // std::cout << "Debug: " << Token << std::endl;

    return false;
}

bool Lexer::IsDeclarator(std::string& Token)
{
    for(int i = 0; i < 3; i++)
    {
        if(KEYWORDS::declarator[i] == Token)
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
        Console::PrintError("The first letter of variable name, cannot be a number!");
        return false;
    }

    return true;
}