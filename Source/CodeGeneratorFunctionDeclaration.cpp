#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateFunctionDeclaration(AstNode* node)
{
    return this->VisitorFunctionDeclaration(node);
}

std::string CodeGenerator::VisitorFunctionDeclaration(AstNode* node)
{
    if(node->token->value == KEYWORDS::TFUN)
    {
        FunctionDeclarationCodeStack.push_back(TARGET_CODE::T_FUN);
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::COLON)
        return this->VisitorFunctionDeclaration(node->right); 

    if(node->token->type == NAME::TYPE)
    {
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->type == NAME::IDENTIFIER)
    {
        FunctionDeclarationCodeStack.push_back(node->token->value);
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::OPEN_PARAM)
    {
        FunctionDeclarationCodeStack.push_back(TARGET_CODE::T_OPEN_PARAM);
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->value == KEYWORDS::TVAR   ||
       node->token->value == KEYWORDS::TCONST )
    {
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::COMMA)
    {
        FunctionDeclarationCodeStack.push_back(TARGET_CODE::T_COMMA);
        return this->VisitorFunctionDeclaration(node->right);
    }

    if(node->token->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        FunctionDeclarationCodeStack.push_back(TARGET_CODE::T_CLOSE_PARAM);
        FunctionDeclarationCodeStack.push_back(this->VisitorStatement(node->StatementList));
        // return this->VisitorFunctionDeclaration(node->right);
        return this->CommitFunctionDeclaration();
    }

    return EMPTY;
}

std::string CodeGenerator::CommitFunctionDeclaration()
{
    std::string build;
    for(auto item : this->FunctionDeclarationCodeStack) build += item;
    this->FunctionDeclarationCodeStack.clear();
    return build;
}




