#include "../headers/parser.hpp"

Expression* Parser::BuildExpression(Tokens* tokenList)
{
    auto expression  = new Expression();

    bool enableFindToken = (tokenList == nullptr);

    Token* history     = nullptr;
    int parenCounter   = 0;
    int executeCounter = 0;

    std::vector<Token*> BuildTokenList;
    std::stack<Token*> StoreOpenParenToken;

    while(true)
    {
        Token* token = nullptr;

        if(enableFindToken)
            token = this->GetNextToken("");
        else
            token = tokenList->Shift();

        if(token == nullptr) 
        {
            // # The Situation where the tokenlist is passed, the ';' will not have
            // # Then, this verification is a breakpoint. 
            if(!enableFindToken) break;

            Output::PrintCustomizeError("Line: " + std::to_string(this->lineHistory) + " | Syntax error: ", "missing ';' at the end of the expression");
            exit(EXIT_FAILURE);
        }

        if(token->value == DELIMITER::T_EOF)
        {
            if(history != nullptr) 
            {
                if(history->type  == TYPE_TOKEN::T_BOOL_LITERAL   ||
                   history->type  == TYPE_TOKEN::T_CHAR_LITERAL   ||
                   history->type  == TYPE_TOKEN::T_FLOAT_LITERAL  ||
                   history->type  == TYPE_TOKEN::T_INT_LITERAL    ||
                   history->type  == TYPE_TOKEN::T_IDENTIDIER     ||
                   history->type  == TYPE_TOKEN::T_STRING_LITERAL ||
                   history->value == DELIMITER::T_CLOSE_PAREM     )
                {
                    break;
                }
            }

            ThrowError(token, "Unexpected token");
        }

        if(history == nullptr)
        {
            if(token->value == DELIMITER::T_OPEN_PAREM)
            {
                parenCounter++;
                history = token;
                BuildTokenList.push_back(token);
                StoreOpenParenToken.push(token);
                continue;
            }

            if(token->type == TYPE_TOKEN::T_BOOL_LITERAL   ||
               token->type == TYPE_TOKEN::T_CHAR_LITERAL   ||
               token->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
               token->type == TYPE_TOKEN::T_INT_LITERAL    ||
               token->type == TYPE_TOKEN::T_IDENTIDIER     ||
               token->type == TYPE_TOKEN::T_PREFIX         ||
               token->type == TYPE_TOKEN::T_STRING_LITERAL )
            {
                if(token->type == TYPE_TOKEN::T_IDENTIDIER)
                {
                    switch(this->GetTypeIdentifier(token))
                    {
                        case TYPE_IDENTIFIER::IDENTIFIER_VARIABLE:
                            history = token;                
                            BuildTokenList.push_back(token);
                            continue;
                        break;

                        case TYPE_IDENTIFIER::IDENTIFIER_FUNCTION:
                            history       = token;                
                            auto tmpToken = token->GetCopy();
                            token->value  = this->BuildCallFunction(tmpToken, tokenList)->entity->GetByteCode();
                            BuildTokenList.push_back(token);
                            continue;
                        break;
                    }

                    ThrowError(token, "Identifier not declared in the scope");
                }

                history = token;
                BuildTokenList.push_back(token);
                
                continue;
            }

            ThrowError(token, "Unexpected token");
        }

        if(token->value == DELIMITER::T_OPEN_PAREM) 
        {
            if(history->type == TYPE_TOKEN::T_ARITHMETIC     ||
               history->type == TYPE_TOKEN::T_BOOL_LITERAL   ||
               history->type == TYPE_TOKEN::T_CHAR_LITERAL   ||
               history->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
               history->type == TYPE_TOKEN::T_INT_LITERAL    ||
               history->type == TYPE_TOKEN::T_DELIMITER      ||
               history->type == TYPE_TOKEN::T_IDENTIDIER     ||
               history->type == TYPE_TOKEN::T_LOGICAL        ||
               history->type == TYPE_TOKEN::T_POSTFIX        ||
               history->type == TYPE_TOKEN::T_PREFIX         ||
               history->type == TYPE_TOKEN::T_STRING_LITERAL )
            {
                parenCounter++;
                history = token;                
                BuildTokenList.push_back(token);
                StoreOpenParenToken.push(token);

                continue;
            }

            ThrowError(token, "Unexpected token");
        }

        if(token->value == DELIMITER::T_CLOSE_PAREM) 
        {
            if(history->type == TYPE_TOKEN::T_BOOL_LITERAL   ||
               history->type == TYPE_TOKEN::T_CHAR_LITERAL   ||
               history->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
               history->type == TYPE_TOKEN::T_INT_LITERAL    ||
               history->type == TYPE_TOKEN::T_IDENTIDIER     ||
               history->type == TYPE_TOKEN::T_LOGICAL        ||
               history->type == TYPE_TOKEN::T_POSTFIX        ||
               history->type == TYPE_TOKEN::T_STRING_LITERAL )
            {
                parenCounter--;
                StoreOpenParenToken.pop();

                if(parenCounter < 0)
                    ThrowError(token, "Unexpected closing parentheses");
                
                history = token;                
                BuildTokenList.push_back(token);
                
                continue;
            }

            ThrowError(token, "Unexpected token");
        }

        if(token->type == TYPE_TOKEN::T_ARITHMETIC)
        {
            if(history->type  == TYPE_TOKEN::T_BOOL_LITERAL   ||
               history->type  == TYPE_TOKEN::T_CHAR_LITERAL   ||
               history->type  == TYPE_TOKEN::T_FLOAT_LITERAL  ||
               history->type  == TYPE_TOKEN::T_INT_LITERAL    ||
               history->type  == TYPE_TOKEN::T_IDENTIDIER     ||
               history->type  == TYPE_TOKEN::T_LOGICAL        ||
               history->type  == TYPE_TOKEN::T_POSTFIX        ||
               history->type  == TYPE_TOKEN::T_STRING_LITERAL ||
               history->value == DELIMITER::T_CLOSE_PAREM     )
            {
                history = token;
                BuildTokenList.push_back(token);
                
                continue;
            }

            ThrowError(token, "Unexpected token");
        }

        if(token->type == TYPE_TOKEN::T_LOGICAL)
        {
            if(history->type == TYPE_TOKEN::T_BOOL_LITERAL   ||
               history->type == TYPE_TOKEN::T_CHAR_LITERAL   ||
               history->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
               history->type == TYPE_TOKEN::T_INT_LITERAL    ||
               history->type == TYPE_TOKEN::T_IDENTIDIER     ||
               history->type == TYPE_TOKEN::T_POSTFIX        ||
               history->type == TYPE_TOKEN::T_STRING_LITERAL )
            {
                history = token;
                BuildTokenList.push_back(token);
                
                continue;
            }

            ThrowError(token, "Unexpected token");
        }

        if(token->type == TYPE_TOKEN::T_BOOL_LITERAL   ||
           token->type == TYPE_TOKEN::T_CHAR_LITERAL   ||
           token->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
           token->type == TYPE_TOKEN::T_INT_LITERAL    ||
           token->type == TYPE_TOKEN::T_IDENTIDIER     ||
           token->type == TYPE_TOKEN::T_STRING_LITERAL )
        {
            if(history->type == TYPE_TOKEN::T_ARITHMETIC ||
               history->type == TYPE_TOKEN::T_DELIMITER  ||
               history->type == TYPE_TOKEN::T_LOGICAL    ||
               history->type == TYPE_TOKEN::T_PREFIX     )
            {
                if(token->type == TYPE_TOKEN::T_IDENTIDIER)
                {
                    switch(this->GetTypeIdentifier(token))
                    {
                        case TYPE_IDENTIFIER::IDENTIFIER_VARIABLE:
                            history = token;                
                            BuildTokenList.push_back(token);
                            continue;
                        break;

                        case TYPE_IDENTIFIER::IDENTIFIER_FUNCTION:
                            history       = token;                
                            auto tmpToken = token->GetCopy();
                            token->value  = this->BuildCallFunction(tmpToken, tokenList)->entity->GetByteCode();
                            BuildTokenList.push_back(token);
                            continue;
                        break;
                    }

                    ThrowError(token, "Identifier not declared in the scope");
                }

                history = token;                
                BuildTokenList.push_back(token);
                
                continue;
            }
        }

        ThrowError(token, "Unexpected token");
    }

    if(parenCounter > 0)
    {
        ThrowError(StoreOpenParenToken.top(), "parentheses opened but never close");
        exit(EXIT_FAILURE);
    }

    expression->TokenVector = BuildTokenList;

    return expression;
}






