#include "../Includes/Parser.hpp"

Parser::Parser(){}

Parser::~Parser(){}

void Parser::RemoveHistory()
{
    this->History.first.clear();
    this->History.second.clear();
}

void Parser::SetHistory(Dictionary Token)
{
    this->History.first = Token.first;
    this->History.second = Token.second;
}

void Parser::RunCheck(Tokens_lst Tokens, uint64_t LineCount)
{
    this->LineCount = LineCount;
    
    for(int i = 0; i < Tokens.size(); i++)
    {
        this->SyntaxCheck(Tokens[i]);
    }
}

void Parser::ExitProgram()
{
    exit(EXIT_FAILURE);
}

void Parser::PrintError(std::string Message)
{
    Console::PrintError("Line: " + std::to_string(this->LineCount) + " | " + Message);
}