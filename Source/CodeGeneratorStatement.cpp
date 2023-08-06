#include "../Include/CodeGenerator.hpp"

std::string CodeGenerator::VisitorStatement(std::vector<std::pair<std::string, AstNode*>> statementList)
{
    this->StatementCodeStack.push_back(TARGET_CODE::T_OPEN_BRACE);
    this->generateWithLet = true;
    int stmtCounter = 1;

    for(auto item : statementList)
    {
        if(item.first == BRANCH_NAME::VARIABLE_DECLARATION)
           this->StatementCodeStack.push_back(this->GenerateVariableDeclaration(item.second));
    
        if(item.first == BRANCH_NAME::RETURN_EXPRESSION)
           this->StatementCodeStack.push_back(this->VisitorExpression(item.second));
    
        if(item.first == BRANCH_NAME::ASSIGNMENT_EXPRESSION)
           this->StatementCodeStack.push_back(this->VisitorAssignmentExpression(item.second));
    
        if(item.first == BRANCH_NAME::CALL_FUNCTION)
           this->StatementCodeStack.push_back(this->GenerateCallFunction(item.second));
        
        if(item.first == BRANCH_NAME::CONDITION_DECLARATION)
        {
           this->StatementCodeStack.push_back(this->GenerateConditionDeclaration(item.second));
           stmtCounter++;
        }
    
        if(item.first == BRANCH_NAME::END_STATEMENT   ||
           item.first == BRANCH_NAME::CLOSE_STATEMENT )
        {
            this->StatementCodeStack.push_back(TARGET_CODE::T_CLOSE_BRACE);
            stmtCounter--;

            if(stmtCounter <= 0)
            {
               this->generateWithLet = false;
               return this->CommitStatement();
            }
        }
    }

    Output::PrintDebug("StmtCount: " + std::to_string(stmtCounter));

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

