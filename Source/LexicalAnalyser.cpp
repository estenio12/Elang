#include "../Include/LexicalAnalyser.hpp"

Lexer::Lexer(){}

Lexer::~Lexer(){}

token_list Lexer::Tokenize(std::string line)
{
    token_list list;
    std::string current_word;

    for(char letter : line)
    {
        if(this->IsNotAlphaNumeric(letter))
        {
            if(Checker::IsValidLine(current_word)) list.push_back(current_word);

            if(letter != DELIMITERS::WHITESPACE[0])
            {
                list.push_back(this->ConvertCharacterToToken(letter));
            }
            
            current_word.clear();
        }
        else
        {
            current_word.push_back(letter);
        }
    }

    return list;
}

token Lexer::ConvertCharacterToToken(char letter)
{
    token ntoken = "";
    ntoken.push_back(letter); 
    return ntoken; 
}

bool Lexer::IsNotAlphaNumeric(char letter)
{
    for(char iterator : ALPHA::ALPHANUMERIC)
    {
        if(letter == iterator)
        {
            return false;
        }
    }

    return true;
}

