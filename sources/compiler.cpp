#include "../headers/compiler.hpp"

Compiler::Compiler(std::string sourcePath)
{
    this->lexer = new Lexer(sourcePath);
}

Compiler::~Compiler()
{
    delete lexer;
}

void Compiler::Run()
{
    auto token = this->lexer->GetNextToken();

    if(token != nullptr)
        Output::PrintDebug("Run: " + token->value + " | " + std::to_string(token->startpos) + " | " + std::to_string(token->endpos));
    else
        Output::PrintDebug("Is Null");
}