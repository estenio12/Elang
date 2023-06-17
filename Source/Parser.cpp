#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
}

Parser::~Parser(){}

void Parser::Parse()
{
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

        switch(this->currentBranch)
        {
            case BRANCH_IDENTIFIER::UNDEFINED:
                this->BindOperation(token);
            break;

            case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
                this->VariableDeclaration(token);
            break;
        }
    }
}

void Parser::BindOperation(Token* token)
{
    // # VARIABLE DECLARATION
    if(token->value == KEYWORDS::TVAR   ||
       token->value == KEYWORDS::TCONST)
    {
        this->currentBranch = BRANCH_IDENTIFIER::VARIABLE_DECLARATION;
        this->VariableDeclaration(token);
    }
}










