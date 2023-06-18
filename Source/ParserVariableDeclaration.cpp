#include "../Include/Parser.hpp"

bool Parser::VariableDeclaration(Token* token)
{
    // # If history is null, is expected the variables declaration 
    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TVAR   ||
           token->value == KEYWORDS::TCONST )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    // # After variables declaration token, is expected the colon 
    if(history->value == KEYWORDS::TVAR   ||
       history->value == KEYWORDS::TCONST )
    {
        if(token->value[0] == DELIMITERS::COLON)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    // # After colon token, is expected a type
    if(history->value[0] == DELIMITERS::COLON)
    {
        if(token->value == TYPE::NAME[TYPE::TBOOL]   ||
           token->value == TYPE::NAME[TYPE::TCHAR]   ||
           token->value == TYPE::NAME[TYPE::TNUMBER] ||
           token->value == TYPE::NAME[TYPE::TTEXT]   ||
           token->value == TYPE::NAME[TYPE::TVOID]   )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    // # After type token, is expected an identifier 
    if(history->value == TYPE::NAME[TYPE::TBOOL]   ||
       history->value == TYPE::NAME[TYPE::TCHAR]   ||
       history->value == TYPE::NAME[TYPE::TNUMBER] ||
       history->value == TYPE::NAME[TYPE::TTEXT]   ||
       history->value == TYPE::NAME[TYPE::TVOID]   )
    {
        if(token->type == NAME::IDENTIFIER)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    // # After identifier token, is expected '=' or ';'
    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::ASSIGN)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else if(token->value[0] == DELIMITERS::EOL)
        {
            this->VariableDeclarationCommit();
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    if(history->value == DELIMITERS::ASSIGN)
    {
        if(token->value[0] == DELIMITERS::OPEN_PARAM ||
           token->type     == NAME::ATTRIBUTION      ||
           token->type     == NAME::BOOLEAN          ||
           token->type     == NAME::IDENTIFIER       ||
           token->type     == NAME::STRING           ||
           token->type     == NAME::CHARACTER        ||
           token->type     == NAME::NUMBER           )
        {
            this->buffer.push_back(token);
            this->history = token;
            return true;
        }
        else
        {
            this->ThrowError("unexpected token '" + token->value + "'", token->startPos);
        }
    }

    if(history->value[0] == DELIMITERS::OPEN_PARAM ||
       history->type     == NAME::ATTRIBUTION      ||
       history->type     == NAME::BOOLEAN          ||
       history->type     == NAME::IDENTIFIER       ||
       history->type     == NAME::STRING           ||
       history->type     == NAME::CHARACTER        ||
       history->type     == NAME::NUMBER           )
    {
        if(token->value == DELIMITERS::OPEN_PARAM)
        {
            this->buffer.push(token);
            this->history = token;
            return true;
        }
    }

    return false;
}

void Parser::VariableDeclarationCommit()
{
    this->InsertAstNode(BRANCH_NAME::VARIABLE_DECLARATION, this->buildingNode);
    this->ResetState();
}