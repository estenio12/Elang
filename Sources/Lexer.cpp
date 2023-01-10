#include "../Includes/Lexer.hpp"

Lexer::Lexer(){}

Lexer::~Lexer(){}

void Lexer::Tokenaze(const std::string line)
{
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
            this->IdentifyToken(CurrentWord);
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
                        this->IdentifyToken(CurrentDigit);
                        CurrentDigit.clear();
                    }

                    this->IdentifyChar(line[i]);
                }
            }
        }
        
    }

    // return nullptr;
}

void Lexer::IdentifyToken(const std::string Token)
{
    if(Token.size() > 0)
    {
        std::cout << "Debug: " << Token << " | " << Token.size() << std::endl;
    }
}

void Lexer::IdentifyChar(const char Token)
{
    std::cout << "Debug: " << Token << std::endl;
}

bool Lexer::IsDeclarator(const std::string& Token)
{
    return false;
}