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
    this->lexer->GetNextToken();
}