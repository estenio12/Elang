#include "../Include/Parser.hpp"

bool Parser::BuildParameterList(Token* token)
{
    if(history->value[0] == DELIMITERS::OPEN_PARAM ||
       history->value[0] == DELIMITERS::COMMA)
    {
        if(token->value == KEYWORDS::TVAR   ||
           token->value == KEYWORDS::TCONST )
        {   
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TVAR   ||
       history->value == KEYWORDS::TCONST )
    { 
        if(token->value[0] == DELIMITERS::COLON)
        {
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->value[0] == DELIMITERS::COLON)
    {
        if(token->value == NAME::NUMBER    ||
           token->value == NAME::BOOLEAN   ||
           token->value == NAME::STRING    ||
           token->value == NAME::CHARACTER )
        {
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }
    }

    if(history->value == NAME::NUMBER    ||
       history->value == NAME::BOOLEAN   ||
       history->value == NAME::STRING    ||
       history->value == NAME::CHARACTER )
    {
        if(token->type == NAME::IDENTIFIER)
        {
            this->parameterList.push_back(std::make_pair(this->history->value, token->value));
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::COMMA)
        {
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->AddDeepCounter();
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->BuildParameterListCommit();
            return true;
        }
    }

    this->ThrowError(token);
    return false;
}

void Parser::BuildParameterListCommit()
{
    switch(this->observer)
    {
        case BRANCH_IDENTIFIER::FUNCTION_DECLARATION:
            this->BuildParameterListCommitForFunction();
        break;
        
        default:
            Output::PrintCustomizeError("Compiler internal error in build parameter list: ", "No observer found!");
            exit(EXIT_FAILURE);
        break;
    }
}

void Parser::InsertParameterListNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->ParameterListBuildingNode == nullptr)
    {
        this->ParameterListBuildingNode = node;
        this->history = token;
    }
    else
    {
        auto lastNode = this->FindLastNode(ParameterListBuildingNode, direction);

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::BuildParameterListCommitForFunction()
{
    this->AssignCurrentBranch(BRANCH_IDENTIFIER::FUNCTION_DECLARATION);
    
    auto functionIdentifier = this->IDFunTable->FindObjectIdentifier(this->currentScope, this->currentFunctionType);
    functionIdentifier->paramList = this->parameterList;
    this->parameterList.clear();
    
    auto lastNode = this->FindLastNode(this->buildingNode, AST_DIRECTION::RIGHT);

    if(lastNode == nullptr)
    {
        Output::PrintCustomizeError("Compiler internal error in build parameter list: ", "function declaration no found!");
        exit(EXIT_FAILURE);
    }
    else
        lastNode->right = this->ParameterListBuildingNode;
}

