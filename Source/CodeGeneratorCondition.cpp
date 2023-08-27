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

        if(node->token->value == KEYWORDS::TFOR)
        {
            return this->VisitorForStatementConditionDeclaration(node);
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

std::string CodeGenerator::VisitorForStatementConditionDeclaration(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->token->value == KEYWORDS::TFOR)
        {
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_FOR);
            return this->VisitorForStatementConditionDeclaration(node->right);
        }

        if(node->token->value[0] == DELIMITERS::OPEN_PARAM)
           return this->VisitorForStatementConditionDeclaration(node->right);
    
        if(node->token->value == KEYWORDS::TIN)
        {
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_IN);
            auto result = this->VisitorExpression(node->right);
            this->ConditionDeclarationCodeStack.push_back(result);
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_FOR_END);
            return this->CommitConditionDeclaration();
        }

        if(node->token->value == KEYWORDS::TAT)
        {
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_AT);
            auto result = this->VisitorExpression(node->right);
            this->ConditionDeclarationCodeStack.push_back(result);
            this->ConditionDeclarationCodeStack.push_back(TARGET_CODE::T_FOR_END);
            return this->CommitConditionDeclaration();
        }
    }

    return EMPTY;
}


