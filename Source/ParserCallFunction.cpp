#include "../Include/Parser.hpp"

AstNode* Parser::CallFunction(Token* token)
{
    if(this->CallFunctionState == BRANCH_IDENTIFIER::EXPRESSION)
    {
        auto result = this->Expression(token, this->CurrentArgumentExpectedType);
    
        if(result != nullptr)
        {
            this->CallFunctionState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->CallFunctionBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetExpressionBuildingNode();
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
        this->CallFunctionState = BRANCH_IDENTIFIER::EXPRESSION;
        this->CurrentArgumentListFunctionName = token->value;
        auto entity = this->IDFunTable->FindObjectIdentifier(token->value);
        this->ExpressionCommaCounter = entity->paramList.size() - 1;
        this->CurrentArgumentExpectedType = this->GetNextArgumentType();
        return this->CallFunction(token);
    }

    this->ThrowError(token);
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





