#include "../Include/Parser.hpp"

bool Parser::FunctionDeclaration(Token* token)
{
    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TFUN)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->observer = BRANCH_IDENTIFIER::FUNCTION_DECLARATION; 
            this->history  = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TFUN)
    {
        this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    if(history->value[0] == DELIMITERS::COLON)
    {
        if(token->value == NAME::NUMBER    ||
           token->value == NAME::STRING    ||
           token->value == NAME::CHARACTER ||
           token->value == NAME::VOID      ||
           token->value == NAME::BOOLEAN   ||
           token->value == NAME::NUMBER    )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->currentFunctionType = this->GetExpectedType(token);
            return true;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::TYPE)
    {
        if(token->type == NAME::IDENTIFIER)
        {
            if(this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep) ||
               this->IDFunTable->ExistIdentifier(token->value))
               this->ThrowError("Duplicate identifier in function declaration '" +token->value+ "'" , token->startPos);
            
            auto tempID = this->IDFunTable->CreateRow(token->value, this->currentFunctionType);

            this->IDFunTable->InsertFunctionID(tempID);
            this->currentScope = token->value;
            this->history      = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::OPEN_PARAM)
        {
            this->AddParemCounter();
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        
        this->ThrowError(token);
    }

    if(history->value[0] == DELIMITERS::OPEN_PARAM)
    {
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->AddDeepCounter();
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
        else
        {
            this->currentBranch = BRANCH_IDENTIFIER::BUILD_PARAMETER_LIST;
            this->BuildParameterList(token);
            return true;
        }
    }

    if(history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value[0] == DELIMITERS::EOL)
        {
            this->RemoveDeepCounter();
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->FunctionDeclarationCommit();
            return true;
        }
        else
        {
            this->FunctionBodyDeclaration(token);
            return true;
        }
    }

    this->ThrowError(token);
    return false;
}

void Parser::FunctionDeclarationCommit()
{
    this->InsertAstNode(BRANCH_NAME::FUNCTION_DECLARATION, this->buildingNode);
    this->currentScope        = STANDARD_SCOPE_NAME::GLOBALSCOPE;
    this->currentFunctionType = EXPECTED_TYPE::TUNDEFINED;
    this->ResetState();
}

bool Parser::FunctionBodyDeclaration(Token* token)
{
    

    this->ThrowError(token);
    return false;
}


