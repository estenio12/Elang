#include "../Include/Parser.hpp"

AstNode* Parser::CallFunction(Token* token)
{
    if(this->CallFunctionState == BRANCH_IDENTIFIER::CALL_FUNCTION)
    {
        if(this->history == nullptr)
        {
            if(token->value[0] == DELIMITERS::CLOSE_PARAM)
            {
                this->CallFunctionState = BRANCH_IDENTIFIER::UNDEFINED;
                this->InsertCallFunctionBuildNode(token, AST_DIRECTION::RIGHT);
                this->history = nullptr;
                return CallFunctionBuildingNode;
            }
        }

        auto result = this->ArgumentList(token);
    
        if(result != nullptr)
        {
            this->CallFunctionState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->CallFunctionBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetArgumentListBuildNode();
                return this->CallFunctionBuildingNode;
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Call function structure not found!");
            }
        }

        return nullptr;
    }    

    if(history == nullptr)
    {
        if(token->type == NAME::IDENTIFIER)
        {
            this->InsertCallFunctionBuildNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::OPEN_PARAM)
        {
            this->CallFunctionState = BRANCH_IDENTIFIER::CALL_FUNCTION;
            this->InsertCallFunctionBuildNode(token, AST_DIRECTION::RIGHT);
            this->history = nullptr;
            return nullptr;
        }
    }
}

void Parser::InsertCallFunctionBuildNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->CallFunctionBuildingNode == nullptr)
    {
        this->CallFunctionBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(CallFunctionBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetCallFunctionBuildNode()
{
    this->CallFunctionBuildingNode = nullptr;
}
