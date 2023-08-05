#include "../Include/Parser.hpp"

AstNode* Parser::CloseStatment(Token* token)
{
    if(this->ConditionStmtCounter > 0)
       this->RemoveConditionStmtCounter();

    return new AstNode(token);
}



