#include "../Include/CodeGenerator.hpp"

void CodeGenerator::VisitorArithmeticOperation(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->token->value[0] == DELIMITERS::EOL)
        {
            this->ArithmeticOperationCodeStack.push_back(TARGET_CODE::T_EOL);
            this->CommitArithmeticOperation();
        }
        else
        {
            this->ArithmeticOperationCodeStack.push_back(node->token->value);
            this->VisitorArithmeticOperation(node->right);
        }
    }
}

void CodeGenerator::CommitArithmeticOperation()
{
    switch(this->oldOperation)
    {
        case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
            for(auto item : this->ArithmeticOperationCodeStack) 
                VariableDeclarationCodeStack.push_back(item);
            this->ArithmeticOperationCodeStack.clear();
            this->CommitVariableDeclaration();
        break;

        default:
            std::string build;
            for(auto item : this->ArithmeticOperationCodeStack) build += item;
            this->ArithmeticOperationCodeStack.clear();
            this->CodeStack.push_back(build);
        break;
    }
}