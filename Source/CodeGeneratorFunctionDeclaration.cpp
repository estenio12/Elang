#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::GenerateFunctionDeclaration(AstNode* node)
{
    return this->VisitorFunctionDeclaration(node);
}

std::string CodeGenerator::VisitorFunctionDeclaration(AstNode* node)
{
    if(node->token->value == KEYWORDS::TFUN)
    {
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
        std::string buildFunctionInterface = this->CreateFunctionInterface(node);
        this->FunctionsInterfaces.push_back(buildFunctionInterface);
        
        std::string buildFunctionImplementation = this->CreateFunctionImplementationHeader(node);
        auto lastNode = this->FindLastNode(node, AST_DIRECTION::RIGHT);
        
        buildFunctionImplementation += this->VisitorStatement(lastNode->StatementList);
        this->FunctionsImplementations.push_back(buildFunctionImplementation);
        
        return EMPTY;
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




