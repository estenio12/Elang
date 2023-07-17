#include "../Include/Parser.hpp"

AstNode* Parser::ArgumentList(Token* token)
{
    if(history == nullptr)
    {
        auto currentArgumentType = this->GetNextArgumentType();
        // this->InsertExpressionNode(token, );
    }
}

void Parser::InsertArgumentListBuildNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->ArgumentListBuildingNode == nullptr)
    {
        this->ArgumentListBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(ArgumentListBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::IncrementArgumentIndex()
{
    this->ArgumentIndex++;
}

void Parser::ResetArgumentListBuildNode()
{
    this->ArgumentListBuildingNode = nullptr;
    this->ArgumentIndex = 0;
    this->CurrentArgumentListFunctionName.clear();
}

std::string Parser::GetNextArgumentType()
{
    auto result = this->IDFunTable->FindObjectIdentifier(this->CurrentArgumentListFunctionName);

    if(result == nullptr)
    {
        Output::PrintCustomizeError("Compiler internal error: ", "(In argumentList) Parameter list no found.");
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


