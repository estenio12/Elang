#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer){}

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










