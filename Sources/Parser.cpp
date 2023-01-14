#include "../Includes/Parser.hpp"

Parser::Parser(){}

Parser::~Parser(){}

void Parser::AddHistory(std::string key, std::string value)
{
    this->History.first  = key;
    this->History.second = value;
}

void Parser::RemoveHistory()
{
    this->History.first.clear();
    this->History.second.clear();
}

void Parser::RunCheck(Tokens_lst Tokens)
{
    for(int i = 0; i < Tokens.size(); i++)
    {
        this->SintaxCheck(Tokens[i].first);
    }
}