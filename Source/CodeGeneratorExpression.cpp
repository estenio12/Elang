#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::VisitorExpression(AstNode* node)
{
    if(node->token->value[0] == DELIMITERS::EOL)
    {
        this->ExpressionCodeStack.push_back(TARGET_CODE::T_EOL);
        return this->CommitExpression(); 
    }

    this->ExpressionCodeStack.push_back(node->token->value);
    return this->VisitorExpression(node->right);
}

std::string CodeGenerator::CommitExpression()
{
    std::string build;
    for(auto item : this->ExpressionCodeStack) build += item;
    this->ExpressionCodeStack.clear();
    return build;
}