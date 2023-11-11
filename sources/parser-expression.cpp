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

// Expression* Parser::BuildExpression(Tokens* tokenList)
// {
//     auto expression  = new Expression();

//     if(tokenList == nullptr)
//     {
//         tokenList        = new Tokens();
//         int parenCounter = 0;

//         while(true)
//         {
//             auto token = this->GetNextToken("");

//             if(token->value == DELIMITER::T_OPEN_PAREM) parenCounter++;

//             if(token == nullptr) 
//             {
//                 Output::PrintCustomizeError("Line: " + std::to_string(lexer->lineCounter) + " | Syntax error: ", "missing ';' at the end of the expression");
//                 exit(EXIT_FAILURE);
//             }
//             else if(token->value == DELIMITER::T_EOF   || 
//                     token->value == DELIMITER::T_COMMA )
//             {
//                 break;
//             }
//             else if(token->value == DELIMITER::T_CLOSE_PAREM) 
//             {
//                 parenCounter--;

//                 if(parenCounter < 0)
//                     ThrowError(token, "Unexpected closing parentheses");
                
//                 BuildTokenList.push_back(token);
//             }
//             else 
//             {
//                 if(token->type == TYPE_TOKEN::T_IDENTIDIER)
//                 {
//                     if(this->symbolTable->ExistsFunctionIdentifier(token->value))
//                     {
//                         auto hash_name = this->GenerateCallFunctionHash();
                        
//                         auto token_copy = token->GetCopy();
//                         token_copy->value = hash_name;
//                         token_copy->IsStorageInHashTable = true;

//                         BuildTokenList.push_back(token_copy);

//                         expression->CallTable
//                         .push_back
//                         (
//                             std::make_pair
//                             (
//                                 hash_name, 
//                                 this->BuildCallFunction(token)
//                             )
//                         );
//                     }
//                     else
//                         BuildTokenList.push_back(token);
//                 }
//                 else
//                     BuildTokenList.push_back(token);
//             }
//         }
//     }

//     // # Was request a new expression, but not have, then, will return nullptr for sinalize this.
//     if(tokenList->GetSize() <= 0) return nullptr;

//     expression->operation = ParserExpression(tokenList, expression, 0);

//     return expression;
// }

// BinaryOperation* Parser::ParserExpression(Tokens* tokenList, Expression* expr, uint8_t minPrecedence = 0)
// {
//     auto left = ParserPrimary(tokenList, expr);

//     while(tokenList->GetSize() > 0 && 
//           tokenList->GetFirstData()->type == TYPE_TOKEN::T_ARITHMETIC &&
//           GetPrecedenceValue(tokenList->GetFirstData()) >= minPrecedence)
//     {
//         auto tokenOperator = tokenList->Shift();
//         auto right = ParserExpression(tokenList, expr, GetPrecedenceValue(tokenOperator) + 1);
//         left       = new BinaryOperation(left, tokenOperator, right);
//     }

//     return left;
// }

// BinaryOperation* Parser::ParserPrimary(Tokens* tokenList, Expression* expr)
// {
//     auto token = tokenList->Shift();

//     if(token->value == DELIMITER::T_OPEN_PAREM)
//     {
//         auto expression = ParserExpression(tokenList, expr);

//         auto next_token = tokenList->Shift();

//         if(next_token->value == DELIMITER::T_OPEN_PAREM)
//             this->ThrowError(next_token, "Expected closing paratheses");

//         return expression;
//     }
//     else if(token->type == TYPE_TOKEN::T_INT_LITERAL    ||
//             token->type == TYPE_TOKEN::T_FLOAT_LITERAL  ||
//             token->type == TYPE_TOKEN::T_IDENTIDIER     ||
//             token->type == TYPE_TOKEN::T_STRING_LITERAL )
//     {
//         if(token->type == TYPE_TOKEN::T_STRING_LITERAL)
//             expr->IsConcatenation = true;

//         if(token->type == TYPE_TOKEN::T_IDENTIDIER)
//         {
//             expr->IsLiteralOperation = false;

//             // # Check identifier
//             if(this->symbolTable->ExistsIdentifier(token->value, this->currentScope, currentDeep))
//             {
//                 return new BinaryOperation(nullptr, token, nullptr);
//             }
//             // else if(this->symbolTable->ExistsFunctionIdentifier(token->value))
//             // {
//             //     auto nexpr = new BinaryOperation(nullptr, nullptr, nullptr);
//             //     nexpr->IsCallFuncion = true;
//             //     nexpr->call_function = this->BuildCallFunction(token)->branch_call_function_declaration;
//             //     return nexpr;
//             // }
//             // else if(expr->ExistCallFunctionID(token->value))
//             else if(token->IsStorageInHashTable)
//             {
//                 return new BinaryOperation(nullptr, token, nullptr);
//             }
//             else
//                 this->ThrowError(token, "Identifier not declarad in scope");
//         }
            
//         return new BinaryOperation(nullptr, token, nullptr);
//     }

//     this->ThrowError(token, "Unexpected token");
//     return nullptr;
// }

// uint8_t Parser::GetPrecedenceValue(Token* token)
// {
//     if(token->value == ARITHMETIC::T_PLUS        ||
//        token->value == ARITHMETIC::T_MINUS       ||
//        token->value == ARITHMETIC::T_PLUS_EQ     ||
//        token->value == ARITHMETIC::T_MINUS_EQ    ||
//        token->value == ARITHMETIC::T_AND         ||
//        token->value == ARITHMETIC::T_OR          ||
//        token->value == ARITHMETIC::T_SHIFT_LEFT  ||
//        token->value == ARITHMETIC::T_SHIFT_RIGHT )
//     {
//         return 1;
//     }

//     if(token->value == ARITHMETIC::T_MUL    ||
//        token->value == ARITHMETIC::T_DIV    ||
//        token->value == ARITHMETIC::T_MUL_EQ ||
//        token->value == ARITHMETIC::T_DIV_EQ ||
//        token->value == ARITHMETIC::T_MOD    )
//     {
//         return 2;
//     }

//     if(token->value == ARITHMETIC::T_POW) return 3;

//     ThrowError(token, "Invalid arithmetic operator");
//     return 0;
// }





