#include "../Include/Parser.hpp"

AstNode* Parser::CloseStatment(Token* token)
{
    if(token->value == KEYWORDS::TEND)
    {
        int GetID = this->IDTableScope->CloseScope();
        this->IDTable->RemoveID(GetID);

        if(this->ConditionStmtCounter > 0)
           this->RemoveConditionStmtCounter();
        
        return new AstNode(token);
    }

    this->ThrowError(token);
    return nullptr;
}



