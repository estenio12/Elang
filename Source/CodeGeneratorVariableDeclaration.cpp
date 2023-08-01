#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateVariableDeclaration(AstNode* node)
{
    return this->VisitorVariableDeclaration(node);
}

std::string CodeGenerator::VisitorVariableDeclaration(AstNode* node)
{
    if(node->token->value == KEYWORDS::TVAR)
    {
        std::string declaration = (this->generateWithLet) ? TARGET_CODE::T_LET : TARGET_CODE::T_VAR;
        this->VariableDeclarationCodeStack.push_back(declaration);
        return this->VisitorVariableDeclaration(node->right);
    }
    
    if(node->token->value == KEYWORDS::TCONST)
    {
        this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_CONST);
        return this->VisitorVariableDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::COLON)
    {
        return this->VisitorVariableDeclaration(node->right);
    }
    
    if(node->token->type == NAME::TYPE)
    {
        this->VariableDeclarationCurrentType = node->token->value;
        return this->VisitorVariableDeclaration(node->right);
    }

    if(node->token->type == NAME::IDENTIFIER)
    {
        this->VariableDeclarationCodeStack.push_back(node->token->value);
        return this->VisitorVariableDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::ASSIGN)
    {
        this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_ASSING);
        auto expression = this->VisitorExpression(node->right);
        this->VariableDeclarationCodeStack.push_back(expression);
        return this->CommitVariableDeclaration();
    }

    if(node->token->type == NAME::TEXT ||
        node->token->type == NAME::CHAR)
    {
        this->VariableDeclarationCodeStack.push_back(this->ConvertToString(node->token->value));
        return this->VisitorVariableDeclaration(node->right);
    }

    if(node->token->type == NAME::NUMBER  ||
        node->token->type == NAME::BOOLEAN )
    {
        this->VariableDeclarationCodeStack.push_back(node->token->value);
        return this->VisitorVariableDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::EOL)
    {
        this->VariableDeclarationCodeStack.push_back(TARGET_CODE::T_EOL);
        return this->CommitVariableDeclaration();
    }

    return EMPTY;
}

std::string CodeGenerator::CommitVariableDeclaration()
{
    std::string build;
    for(auto item : this->VariableDeclarationCodeStack) build += item;
    this->VariableDeclarationCodeStack.clear();
    return build;
}





