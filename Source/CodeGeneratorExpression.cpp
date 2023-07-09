#include "../Include/CodeGenerator.hpp"

void CodeGenerator::VisitorExpression(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->token->value[0] == DELIMITERS::EOL)
        {
            this->ExpressionCodeStack.push_back(TARGET_CODE::T_EOL);
            this->ResetExpression();
        }
        else
        {
            this->ExpressionCodeStack.push_back(node->token->value);
            this->VisitorExpression(node->right);
        }
    }
}

void CodeGenerator::ResetExpression()
{
    switch(this->oldOperation)
    {
        case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
            for(auto item : this->ExpressionCodeStack) 
                VariableDeclarationCodeStack.push_back(item);
            this->ExpressionCodeStack.clear();
            this->ResetVariableDeclaration();
        break;

        default:
            std::string build;
            for(auto item : this->ExpressionCodeStack) build += item;
            this->ExpressionCodeStack.clear();
            this->CodeStack.push_back(build);
        break;
    }
}