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

    this->CheckParentheses();
}

void Parser::ExitProgram()
{
    exit(EXIT_FAILURE);
}

void Parser::PrintError(std::string Message)
{
    Console::PrintError("Line: " + std::to_string(this->LineCount) + " | " + Message);
}

void Parser::CloseDeclaration()
{
    this->CallbackLevel();
    this->DeclaratorIsUp = false;
    this->RemoveHistory();
}

void Parser::CallbackLevel()
{
    this->Level--;

    if(this->Level <= 0) this->Level = 0;
}

void Parser::AddParanOpen()
{
    this->ParanOpen++;
}

void Parser::RemoveParanOpen()
{
    this->ParanOpen--;
}

void Parser::CheckParentheses()
{
     if(this->ParanOpen > 0)
    {
        this->PrintError("Sintax Error | parentheses open but never closed!");
    }
    
    if(this->ParanOpen < 0)
    {
        this->PrintError("Sintax Error | parentheses close but never opened!");
    }
}