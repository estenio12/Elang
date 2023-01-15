#include "../Includes/Parser.hpp"

bool Parser::SintaxCheck(Dictionary Token)
{
    if(Level == 0)
    {
        if(this->CheckEmptyHistory(Token)) return true;
    }

    return false;
}

bool Parser::CheckEmptyHistory(Dictionary& Token)
{
    if(History.first.empty())
    {
        if(Token.first == NAMES::DECLARATOR) 
        { 
            this->DeclaratorIsUp = true;
            this->History = Token;

            return true; 
        }

        Console::PrintError("Sintax error! Expected a declarator | " + Token.second);
        return false;
    }

    return false;
}