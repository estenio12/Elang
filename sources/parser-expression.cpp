#include "../headers/parser.hpp"

Expression* Parser::BuildExpression()
{
    auto expression = new Expression();

    return nullptr;
}

BinaryOperation* Parser::ParserExpression(Tokens* tokenList, uint8_t minPrecedence = 0)
{
    auto left = ParserPrimary(tokenList);

    while(tokenList->GetSize() > 0 && 
          tokenList->GetFirstData()->type == TYPE_TOKEN::T_ARITHMETIC &&
          )
    {
        
    }

    return nullptr;
}

BinaryOperation* ParserPrimary(Tokens* tokenList)
{
    auto token = tokenList->Shift();

    if(token->value == DELIMITER::T_OPEN_PARAM)
    {
        auto expression = ParserExpression(tokenList);

        this->ExpectValue(tokenList->Shift(), "Expected closing paratheses");

        return expression;
    }
    else if(token->type == TYPE_TOKEN::T_INT_LITERAL    ||
            token->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
            token->type == TYPE_TOKEN::T_IDENTIDIER     ||
            token->type == TYPE_TOKEN::T_STRING_LITERAL )
    {
        return new BinaryOperation(nullptr, token, nullptr);
    }

    this->ThrowError(token, "Unexpected token");
    return nullptr;
}





