#include "../Include/Parser.hpp"

AstNode* Parser::Assignment(Token* token)
{
    if(this->AssignmentState == BRANCH_IDENTIFIER::EXPRESSION)
    {
        auto result = this->Expression(token, this->AssignmentExpectedType);
    
        if(result != nullptr)
        {
            this->AssignmentState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->AssignmentBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetExpressionBuildingNode();
                return this->AssignmentBuildingNode;
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Assignment expression structure not found!");
            }
        }

        return nullptr;
    }

    if(history == nullptr)
    {
        if(token->type == NAME::IDENTIFIER)
        {
            if(!this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep) &&
               !this->IDFunTable->ExistIdentifier(token->value))
            {
                this->ThrowError("Variable not declared in scope '" + token->value + "'", token->startPos + 1);
            }

            auto obj = this->IDTable->FindObjectIdentifier(token->value);

            if(obj == nullptr)
            {
                auto objFunction = this->IDFunTable->FindObjectIdentifier(token->value);
                this->AssignmentExpectedType = objFunction->type;
            }
            else
            {
                this->AssignmentExpectedType = obj->typeValue;
            }

            this->InsertAssignmentBuildNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::ASSIGN)
        {
            this->InsertAssignmentBuildNode(token, AST_DIRECTION::RIGHT);
            this->AssignmentState = BRANCH_IDENTIFIER::EXPRESSION;
            this->history = nullptr;
            return nullptr;
        }

        this->ThrowError(token);
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::InsertAssignmentBuildNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->AssignmentBuildingNode == nullptr)
    {
        this->AssignmentBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(AssignmentBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetAssignmentBuildNode()
{
    this->AssignmentBuildingNode = nullptr;
}



