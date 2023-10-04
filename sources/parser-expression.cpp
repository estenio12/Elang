#include "../headers/parser.hpp"

Expression* Parser::BuildExpression()
{
    auto expression = new Expression();
    auto tokenList  = new Tokens();

    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) 
        {
            Output::PrintCustomizeError("Line: " + std::to_string(lexer->lineCounter) + " | Syntax error: ", "missing ';' at the end of the expression");
            exit(EXIT_FAILURE);
        }
        else if(token->value == DELIMITER::T_EOF || token->value == DELIMITER::T_COMMA) 
            break;
        else tokenList->AddToken(token);
    }

    expression->operation = ParserExpression(tokenList, expression, 0);

    return expression;
}

BinaryOperation* Parser::ParserExpression(Tokens* tokenList, Expression* expr, uint8_t minPrecedence = 0)
{
    auto left = ParserPrimary(tokenList, expr);

    while(tokenList->GetSize() > 0 && 
          tokenList->GetFirstData()->type == TYPE_TOKEN::T_ARITHMETIC &&
          GetPrecedenceValue(tokenList->GetFirstData()) >= minPrecedence)
    {
        auto tokenOperator = tokenList->Shift();
        auto right = ParserExpression(tokenList, expr, GetPrecedenceValue(tokenOperator) + 1);
        left       = new BinaryOperation(left, tokenOperator, right);
    }

    return left;
}

BinaryOperation* Parser::ParserPrimary(Tokens* tokenList, Expression* expr)
{
    auto token = tokenList->Shift();

    if(token->value == DELIMITER::T_OPEN_PARAM)
    {
        auto expression = ParserExpression(tokenList, expr);

        this->ExpectValue(tokenList->Shift()->value, "Expected closing paratheses");

        return expression;
    }
    else if(token->type == TYPE_TOKEN::T_INT_LITERAL    ||
            token->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
            token->type == TYPE_TOKEN::T_IDENTIDIER     ||
            token->type == TYPE_TOKEN::T_STRING_LITERAL )
    {
        if(token->type == TYPE_TOKEN::T_STRING_LITERAL)
            expr->IsConcatenation = true;

        if(token->type == TYPE_TOKEN::T_IDENTIDIER)
        {
            expr->IsLiteralOperation = false;

            // # Check identifier
            if(!this->symbolTable->ExistsIdentifier(token->value, this->currentScope, currentDeep))
                this->ThrowError(token, "Identifier not declarad in scope");
        }
            
        return new BinaryOperation(nullptr, token, nullptr);
    }

    this->ThrowError(token, "Unexpected token");
    return nullptr;
}

uint8_t Parser::GetPrecedenceValue(Token* token)
{
    if(token->value == ARITHMETIC::T_PLUS        ||
       token->value == ARITHMETIC::T_MINUS       ||
       token->value == ARITHMETIC::T_PLUS_EQ     ||
       token->value == ARITHMETIC::T_MINUS_EQ    ||
       token->value == ARITHMETIC::T_AND         ||
       token->value == ARITHMETIC::T_OR          ||
       token->value == ARITHMETIC::T_SHIFT_LEFT  ||
       token->value == ARITHMETIC::T_SHIFT_RIGHT )
    {
        return 1;
    }

    if(token->value == ARITHMETIC::T_MUL    ||
       token->value == ARITHMETIC::T_DIV    ||
       token->value == ARITHMETIC::T_MUL_EQ ||
       token->value == ARITHMETIC::T_DIV_EQ ||
       token->value == ARITHMETIC::T_MOD    )
    {
        return 2;
    }

    if(token->value == ARITHMETIC::T_POW) return 3;

    ThrowError(token, "Invalid arithmetic operator");
    return 0;
}





