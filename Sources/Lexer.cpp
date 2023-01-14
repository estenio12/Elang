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

                    this->IdentifySpecialChar(ConvertCharToString(line[i]), &Tokens);
                }
            }
        }
        
    }

    for(int i = 0; i < Tokens.size(); i++)
    {
        std::cout << "Debug: " << Tokens[i].first << " | ";
        std::cout << Tokens[i].second << std::endl;
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

            return true;
        }

        // # Check if is type
        if(this->IsType(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::TYPE, Token)
            );

            return true;
        }

        // # Always will the last to be identifiers
        
        if(this->IsNumber(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::NUMBER, Token)
            );

            return true;
        }

        if(this->IsValidIdentifier(Token))
        {
            Tokens->push_back
            (
                std::make_pair(NAMES::IDENTIFIER, Token)
            );

            return true;
        }

        // # Not recognize token
        Console::PrintError("unrecognized token | " + Token);
    }

    return false;
}

bool Lexer::IdentifySpecialChar(std::string Token, Tokens_lst* Tokens)
{
    // # Check if is Relational
    if(this->IsRelational(Token))
    {
        Tokens->push_back
        (
            std::make_pair(NAMES::RELATIONAL, Token)
        );

        return true;
    }

    // # Check if is Assignment
    if(this->IsAssignment(Token))
    {
        Tokens->push_back
        (
            std::make_pair(NAMES::ASSIGNMENT, Token)
        );

        return true;
    }

    for(int i = 0; i < LANG::SIZE_STMT; i++)
    {
        if(LANG::STMT[i] == Token)
        {
            Tokens->push_back
            (
                std::make_pair(LANG::STMTNAME[i], Token)
            );

            return true;
        }
    }

    // # Not recognize token
    Console::PrintError("unrecognized token | " + Token);

    return false;
}

std::string Lexer::ConvertCharToString(const char Letter)
{
    std::string tmp;
    tmp.push_back(Letter);
    return tmp;
}

