#include "../Include/CodeGenerator.hpp"

void CodeGenerator::GenerateVariableDeclaration(AstNode* node)
{
    if(node != nullptr) this->VisitorVariableDeclaration(node);
}

void CodeGenerator::VisitorVariableDeclaration(AstNode* node)
{
    if(node == nullptr)
    {
        this->CommitVariableDeclaration();
    }
    else
    {
        if(node->token->value == KEYWORDS::TVAR)
        {
            this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_VAR);
            this->VisitorVariableDeclaration(node->right);
        }
        
        if(node->token->value == KEYWORDS::TCONST)
        {
            this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_CONST);
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->value[0] == DELIMITERS::COLON)
        {
            this->VisitorVariableDeclaration(node->right);
        }
        
        if(node->token->type == NAME::TYPE)
        {
            this->VariableDeclarationCurrentType = node->token->value;
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->type == NAME::IDENTIFIER)
        {
            this->VariableDeclarationCodeStack.push_back(this->AddWhitespace(node->token->value));
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->value[0] == DELIMITERS::ASSIGN)
        {
            this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_ASSING);
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->type == NAME::STRING ||
           node->token->type == NAME::CHARACTER)
        {
            this->VariableDeclarationCodeStack.push_back(this->ConvertToString(node->token->value));
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->type == NAME::NUMBER  ||
           node->token->type == NAME::BOOLEAN )
        {
            this->VariableDeclarationCodeStack.push_back(node->token->value);
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->value[0] == DELIMITERS::EOL)
        {
            this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_EOL);
            this->VisitorVariableDeclaration(node->right);
        }

        if(node->token->type == NAME::ARITHMETIC)
        {
            this->oldOperation = BRANCH_IDENTIFIER::VARIABLE_DECLARATION;
            this->VisitorArithmeticOperation(node);
            
            for(auto item : this->ArithmeticOperationCodeStack)
            {
                Output::PrintDebug(item);
            }
        }
    }
}

void CodeGenerator::VisitorArithmeticOperation(AstNode* node)
{
    if(node != nullptr)
    {
        if(node->HasLeftNode())
        {
            this->ArithmeticOperationCodeStack.push_back(node->left->token->value);
            this->ArithmeticOperationCodeStack.push_back(node->token->value);
            this->VisitorArithmeticOperation(node->right);
        }
        else if(node->token->type != NAME::ARITHMETIC)
        {
            this->ArithmeticOperationCodeStack.push_back(node->token->value);

            if(node->token->value[0] == DELIMITERS::EOL)
                this->CommitArithmeticOperation();
            else
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

void CodeGenerator::CommitVariableDeclaration()
{
    std::string build;

    for(auto item : this->VariableDeclarationCodeStack) 
    {
        build += item;
    }

    this->VariableDeclarationCodeStack.clear();
    this->CodeStack.push_back(build);
}





