#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateConditionDeclaration(AstNode* node)
{
    return this->VisitorConditionDeclaration(node);
}

std::string CodeGenerator::VisitorConditionDeclaration(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->token->value == KEYWORDS::TIF    ||
           node->token->value == KEYWORDS::TWHILE )
        {
            if(node->token->value == KEYWORDS::TIF)
                this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_IF);
            else
                this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_WHILE);

            auto result = this->VisitorExpression(node->right);
            this->ConditionDeclarationCodeStack.push_back(result);
            return this->CommitConditionDeclaration();
        }

        if(node->token->value == KEYWORDS::TELSE)
        {
            return TARGET_CODE::T_CLOSE_BRACE + 
                   TARGET_CODE::T_ELSE +
                   TARGET_CODE::T_OPEN_BRACE; 
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

