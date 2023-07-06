#include "../Include/Parser.hpp"

AstNode* Parser::Statement(Token* token)
{
    if(this->StatementState == BRANCH_IDENTIFIER::EXPRESSION)
    {
        auto result = this->Expression(token, this->currentFunctionType);

        if(result != nullptr)
        {
            this->StatementState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->StatementBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetExpressionBuildingNode();
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Function declaration structure not found!");
            } 
        }

        return nullptr;
    }

    if(history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value == KEYWORDS::TRETURN)
        {
            this->InsertStatementNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }
        
        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TRETURN)
    {
        this->StatementState = BRANCH_IDENTIFIER::EXPRESSION;
        this->history = token;
        this->InsertStatementNode(token, AST_DIRECTION::RIGHT);
        return nullptr;
    }

    if(history->value[0] == DELIMITERS::EOL)
    {
        if(token->value == KEYWORDS::TEND)
        {
            this->RemoveDeepCounter();
            this->history = token;
            return this->StatementBuildingNode;
        }
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

