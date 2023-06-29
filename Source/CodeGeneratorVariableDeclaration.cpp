#include "../Include/CodeGenerator.hpp"

void CodeGenerator::GenerateVariableDeclaration(AstNode* node)
{
    if(node != nullptr) this->VisitorVariableDeclaration(node);
}

void CodeGenerator::VisitorVariableDeclaration(AstNode* node)
{
    // # This operation was made to exit this task when it finishes
    if(node == nullptr) this->CommitVariableDeclaration();

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
}

void CodeGenerator::CommitVariableDeclaration()
{
    std::string build;

    for(auto item : this->VariableDeclarationCodeStack) 
        build += item;

    this->CodeStack.push_back(build);
}