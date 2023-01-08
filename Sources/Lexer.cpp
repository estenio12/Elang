#include "../Includes/Lexer.hpp"

Lexer::Lexer(){}

Lexer::~Lexer(){}

Tokens_lst* Lexer::Tokenaze(const std::string line)
{
    std::string CurrentWord;
    bool IsLetter = false;
    bool IsDigit  = false;

    for(int i = 0; i < line.size(); i++)
    {
        IsLetter = false;

        for(int j = 0; j < KEYWORDS::letters.size(); i++)
        {
            if(line[i] == KEYWORDS::letters[j])
            {
                IsLetter = true;
            }
        }

        if(IsLetter)
        {
            CurrentWord.push_back(line[i]);
        }
        else
        {
            this->IdentifyToken(CurrentWord);
            CurrentWord.clear();

            for(int j = 0; j < KEYWORDS::digits.size(); j++)
            {
                IsDigit = false;

                if(line[i] == KEYWORDS::digits[j])
                {
                    IsDigit = true;
                }

                // # Check if is a dot of float number
                if(!IsDigit)
                {
                    bool CheckNextLetterIsDigit = false;

                    if(line[i] == LANG::NUMBERFLOAT)
                    {
                        for(int k = 0; k < KEYWORDS::digits.size(); k++)
                        {
                            CheckNextLetterIsDigit = false;

                            if(line[i + 1] == KEYWORDS::digits[k])
                            {
                                CheckNextLetterIsDigit = true;
                            }

                            if(CheckNextLetterIsDigit)
                            {
                                IsDigit = true;
                                break;
                            }
                        }

                        if(!CheckNextLetterIsDigit)
                        {
                            if(line[i] != LANG::WHITESPACE)
                            {
                                this->IdentifyToken(std::to_string(line[i]));
                            }
                        }
                    }
                }
            }
        }

    }

    return nullptr;
}

void Lexer::IdentifyToken(const std::string Token)
{
    Console::Print(Token);
}