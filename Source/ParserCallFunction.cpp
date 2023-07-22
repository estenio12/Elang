#include "../Include/Parser.hpp"

AstNode* Parser::CallFunction(Token* token)
{
    if(history == nullptr)
    {
        auto getEntity = this->IDFunTable->FindObjectIdentifier(token->value);
        this->CurrentArgumentExpectedType = getEntity->type;
    }

    auto result = this->Expression(token, this->CurrentArgumentExpectedType);

    if(result != nullptr)
    {
        // this->CallFunctionState = BRANCH_IDENTIFIER::UNDEFINED;
        // auto lastNode = this->FindLastNode(this->CallFunctionBuildingNode, AST_DIRECTION::RIGHT);
    
        // if(lastNode != nullptr)
        // {
            this->CallFunctionBuildingNode = result;
            this->ResetExpressionBuildingNode();
            return this->CallFunctionBuildingNode;
        // }
        // else
        // {
        //     Output::PrintCustomizeError("Compiler internal error: ", "Call function structure not found!");
        // }
    }

    return nullptr;
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
    this->CurrentArgumentListFunctionName.clear();
    this->ArgumentIndex = 0;
}

std::string Parser::GetNextArgumentType()
{
    auto result = this->IDFunTable->FindObjectIdentifier(this->CurrentArgumentListFunctionName);

    if(result == nullptr)
    {
        Output::PrintCustomizeError("Compiler internal error: ", "(In CallFunction) Parameter list no found.");
        exit(EXIT_FAILURE);
    }
    
    if(this->ArgumentIndex <= result->paramList.size())
    {
        auto type = result->paramList[this->ArgumentIndex].first;
        this->IncrementArgumentIndex();
        return type;
    }

    return this->EMPTY;
}

void Parser::IncrementArgumentIndex()
{
    this->ArgumentIndex++;
}





