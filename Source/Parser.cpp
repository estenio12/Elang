#include "../Include/Parser.hpp"

Parser::Parser(int* lineCounter):lineCounter(lineCounter)
{
    this->syntax = new SyntaxPatternMatch();
}

Parser::~Parser(){}

bool Parser::Parse(token_list list)
{
    for(auto token : list)
    {
        this->buildPattern.push_back(token);
        
        if(this->IsTerminateCharacter(token))
        {
            this->PatternMatch();
            this->ResetBuildPattern();
        }
    }

    return this->AstReady;       
}

void Parser::ResetBuildPattern()
{
    buildPattern.clear();
}

bool Parser::IsTerminateCharacter(token target)
{
    if(target == DELIMITERS::EOL)
    {
        return true;
    }

    return false;
}

void Parser::PatternMatch()
{
    if(this->syntax->CheckVariableDeclaration(this->buildPattern))
        std::cout << "Debug: Syntax OK for variable declaration\n";
    else
        std::cout << "Debug: Syntax ERROR for variable declaration\n";
}









