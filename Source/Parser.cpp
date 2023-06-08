#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
}

Parser::~Parser(){}

void Parser::Parse()
{
    while(!this->lexer->FileIsEnd)
    {
        auto token = this->lexer->GetNextToken();

        if(token[0] != '\0') 
        {
            Output::Print("Debug: " + token);
        }
    }
}










