#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateAssignmentExpression(AstNode* node)
{
    return this->VisitorAssignmentExpression(node);
}

std::string CodeGenerator::VisitorAssignmentExpression(AstNode* node)
{
    if(node->token->type == NAME::IDENTIFIER)
    {
        this->AssignmentExpressionCodeStack.push_back(node->token->value);
        return this->VisitorAssignmentExpression(node->right);
    }

    if(node->token->value[0] == DELIMITERS::ASSIGN)
    {
        this->AssignmentExpressionCodeStack.push_back(TARGET_CODE::T_ASSING);
        auto expression = this->VisitorExpression(node->right);
        this->AssignmentExpressionCodeStack.push_back(expression);
        return this->CommitAssignmentExpression();
    }

    return EMPTY;
}

std::string CodeGenerator::CommitAssignmentExpression()
{
    std::string build;
    for(auto item : this->AssignmentExpressionCodeStack) build += item;
    this->AssignmentExpressionCodeStack.clear();
    return build;
}




