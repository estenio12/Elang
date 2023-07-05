#include "../Include/Parser.hpp"

AstNode* Parser::BuildParameterList(Token* token)
{
    if(history->value[0] == DELIMITERS::OPEN_PARAM ||
       history->value[0] == DELIMITERS::COMMA)
    {
        if(token->value == KEYWORDS::TVAR   ||
           token->value == KEYWORDS::TCONST )
        {   
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
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
            return nullptr;
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
            this->currentParameterType = this->GetExpectedType(token);
            return nullptr;
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
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);

            // # Insert into IDTable
            auto tempID = this->IDTable->CreateRow(token->value, token->value, token->type, 
                                                   this->currentParameterType, this->currentScope, 
                                                   this->currentDeep, false);

            this->IDTable->InsertID(tempID);

            return nullptr;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::COMMA)
        {
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->ResetBuildParameterListStates();
            return nullptr;
        }

        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->AddDeepCounter();
            this->InsertParameterListNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->BuildParameterListCommit();
            this->ResetBuildParameterListStates();
            this->RemoveParemCounter();
            return ParameterListBuildingNode;
        }
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::BuildParameterListCommit()
{
    auto functionIdentifier = this->IDFunTable->FindObjectIdentifier(this->currentScope, this->currentFunctionType);
    functionIdentifier->paramList = this->parameterList;
    this->parameterList.clear();
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

void Parser::ResetParameterListBuildingNode()
{
    this->ParameterListBuildingNode = nullptr;
}

void Parser::ResetBuildParameterListStates()
{
    this->currentParameterType = EXPECTED_TYPE::TUNDEFINED;
}


