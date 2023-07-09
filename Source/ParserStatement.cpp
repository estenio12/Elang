#include "../Include/Parser.hpp"

AstNode* Parser::Statement(Token* token)
{
    if(this->StatementState == BRANCH_IDENTIFIER::RETURN_EXPRESSION)
    {
        auto result = this->Expression(token, this->currentFunctionType);

        if(result != nullptr)
        {
            this->StatementState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->StatementBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
                lastNode->right = result;
            else
                this->StatementBuildingNode = result;

            this->ResetExpressionBuildingNode();
            this->history = nullptr;
        }

        return nullptr;
    }

    if(history == nullptr ||
       history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value == KEYWORDS::TRETURN)
        {
            this->StatementState = BRANCH_IDENTIFIER::RETURN_EXPRESSION;
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = nullptr;
            return nullptr;         
        }
        
        if(token->value == KEYWORDS::TEND)
        {
            this->InsertStatementNode(token, AST_DIRECTION::RIGHT);
            this->RemoveDeepCounter();
            this->history = nullptr;
            return this->StatementBuildingNode;
        }
        
        this->ThrowError(token);
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::InsertStatementNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(StatementBuildingNode == nullptr)
    {
        StatementBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(StatementBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetStatementBuildingNode()
{
    this->StatementBuildingNode = nullptr;
}

