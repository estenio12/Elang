#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateConditionDeclaration(AstNode* node)
{
    return this->VisitorConditionDeclaration(node);
}

std::string CodeGenerator::VisitorConditionDeclaration(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->token->value == KEYWORDS::TIF)
        {
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_IF);
            auto result = this->VisitorExpression(node->right);
            this->ConditionDeclarationCodeStack.push_back(result);
            return this->CommitConditionDeclaration();
        }
    }

    return EMPTY;
}

std::string CodeGenerator::CommitConditionDeclaration()
{
    std::string build;
    for(auto item : this->ConditionDeclarationCodeStack) build += item;
    this->ConditionDeclarationCodeStack.clear();
    return build += TARGET_CODE::T_OPEN_BRACE;
}

