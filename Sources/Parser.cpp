#include "../Includes/Parser.hpp"

Parser::Parser(){}

Parser::~Parser(){}

void Parser::RemoveHistory()
{
    this->History.first.clear();
    this->History.second.clear();
}

void Parser::RunCheck(Tokens_lst Tokens)
{
    for(int i = 0; i < Tokens.size(); i++)
    {
        this->SintaxCheck(Tokens[i]);
    }
}

void Parser::ExitProgram()
{
    exit(EXIT_FAILURE);
}