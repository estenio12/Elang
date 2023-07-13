#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::VisitorStatement(std::vector<std::pair<std::string, AstNode*>> statementList)
{
    this->StatementCodeStack.push_back(TARGET_CODE::T_OPEN_BRACE);
    this->generateWithLet = true;

    for(auto item : statementList)
    {
        if(item.first == BRANCH_NAME::VARIABLE_DECLARATION)
           this->StatementCodeStack.push_back(this->GenerateVariableDeclaration(item.second));
    
        if(item.first == BRANCH_NAME::RETURN_EXPRESSION)
           this->StatementCodeStack.push_back(this->VisitorExpression(item.second));
    
        if(item.first == BRANCH_NAME::END_STATEMENT)
        {
            this->StatementCodeStack.push_back(TARGET_CODE::T_CLOSE_BRACE);
            this->generateWithLet = false;
            return this->CommitStatement();
        }
    }

    this->generateWithLet = false;
    return EMPTY;
}

std::string CodeGenerator::CommitStatement()
{
    std::string build;
    for(auto item : this->StatementCodeStack) build += item;
    this->StatementCodeStack.clear();
    return build;
}

