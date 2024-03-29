#include "../headers/parser.hpp"

Expression* Parser::BuildExpression(const std::vector<std::string> expected_type, Tokens* tokenList)
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
        {
            if(tokenList->GetSize() <= 0) break;
            token = tokenList->Shift();
        }
        
        // # When the token is a function call, it's means they were processed
        if(token->isCallFunction)
        {
            history = token->GetCopy();
            history->type  = TYPE_TOKEN::T_DELIMITER;
            history->value = DELIMITER::T_CLOSE_PAREM;
            BuildTokenList.push_back(token);
            continue;
        }

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
                    switch(this->GetTypeIdentifier(token, expected_type))
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

                if(!this->IsValidDataType(token, expected_type))
                    this->ThrowErrorDataType(token, ConvertTypeTokenToType(token->type), expected_type);

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
            
            if(history->type  == TYPE_TOKEN::T_ARITHMETIC ||
               history->type  == TYPE_TOKEN::T_LOGICAL    ||
               history->type  == TYPE_TOKEN::T_PREFIX     ||
               history->value == DELIMITER::T_COMMA       ||     
               history->value == DELIMITER::T_ASSIGN      )
            {
                if(token->type == TYPE_TOKEN::T_IDENTIDIER)
                {
                    switch(this->GetTypeIdentifier(token, expected_type))
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

                if(!this->IsValidDataType(token, expected_type))
                    this->ThrowErrorDataType(token, ConvertTypeTokenToType(token->type), expected_type);

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

BlockStatement* Parser::BuildBlockStatement(BlockStmtPolicy* policy, std::vector<std::string> expected_type)
{
    auto block_stmt = new BlockStatement(expected_type[0]);
    int endStatmetCount = 1;

    while(endStatmetCount > 0)
    {
        auto stmt_token = this->GetNextToken("Expected 'end' keyword to close function statement");

        if(stmt_token->value == KEYWORD::T_END) 
        {
            MemTools::FreeObjectFromMemory(stmt_token);
            endStatmetCount--;
            continue;
        }
        
        if(stmt_token->value == KEYWORD::T_ELSE) 
        {
            if(!policy->HasPolicy(BLOCK_STMT_POLICY::ALLOW_ELSE_CONDITION))
                this->ThrowError(stmt_token, "the keyword else it's not allow in this context");

            MemTools::FreeObjectFromMemory(stmt_token);
            block_stmt->closeWithElse = true;
            return block_stmt;
        }

        auto operation = this->BindOperation(stmt_token);

        switch(operation)
        {
            case EBRANCH_TYPE::VARIABLE_DECLARATION:
                block_stmt->content.push_back(BuildVariableDeclaration(stmt_token));
            break;

            case EBRANCH_TYPE::RETURN_EXPRESSION:
                if(!policy->HasPolicy(BLOCK_STMT_POLICY::ALLOW_RETURN)) this->ThrowError(stmt_token, "the return expression is not allow for this statement"); 
                if(expected_type[0] == TYPE::T_VOID) this->ThrowError(stmt_token, "the return keyword is invalid for the void function type"); 
                
                block_stmt->content.push_back(BuildReturnExpression(stmt_token, expected_type));
            break;

            case EBRANCH_TYPE::CALL_FUNCTION:
                block_stmt->content.push_back(BuildCallFunction(stmt_token));
                this->ExpectValue(DELIMITER::T_EOF, "Expected ';' after the called function ");
            break;

            case EBRANCH_TYPE::BREAK_EXPRESSION:
                if(!policy->HasPolicy(BLOCK_STMT_POLICY::ALLOW_BREAK)) this->ThrowError(stmt_token, "the break keyword is allow only for loops"); 
                block_stmt->content.push_back(BuildBreakStatement(stmt_token));
            break;

            case EBRANCH_TYPE::WHILE_DECLARATION:
                block_stmt->content.push_back(BuildWhileDeclaration(policy, stmt_token, expected_type));
            break;

            case EBRANCH_TYPE::ASSIGNMENT:
                block_stmt->content.push_back(this->BuildAssignment(stmt_token));
            break;

            case EBRANCH_TYPE::IF_ELSE_CONDITION:
                block_stmt->content.push_back(this->BuildIfElseCondition(policy, stmt_token, expected_type));
            break;

            default:
                ThrowError(stmt_token, "Unexpected token ");
            break;
        }
    }

    return block_stmt;
}




