#include "../Include/Parser.hpp"

AstNode* Parser::ArgumentList(Token* token)
{
    if(history == nullptr)
    {
        
        this->InsertExpressionNode(token, );
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

void Parser::ResetArgumentListBuildNode()
{
    this->ArgumentListBuildingNode = nullptr;
}
