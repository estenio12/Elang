#include "../Include/Parser.hpp"

bool Parser::ArithmeticOperation(Token* token)
{
    if(history->value[0] == DELIMITERS::ASSIGN)
    {
        if(token->type == NAME::IDENTIFIER)
        {
            this->InsertBuffer(token);
            return true;
        }

        if(token->value == )
        {

        }
    }

    return false;
}