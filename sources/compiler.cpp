#include "../headers/compiler.hpp"

Compiler::Compiler(std::string sourcePath)
{
    if(IsNotValidPath(sourcePath))
    {
        Output::PrintCustomizeError("Fatal Error: ", "source file not found!");
        exit(EXIT_FAILURE);
    }

    this->lexer = new Lexer(sourcePath);
    this->debug = new DebugToken();
}

Compiler::~Compiler()
{
    delete lexer;
}

bool Compiler::IsNotValidPath(std::string sourcePath)
{
    if(sourcePath.empty()) return false;
    return !std::filesystem::exists(std::filesystem::path(sourcePath));
}

void Compiler::Run()
{
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

        // debug->printToken(token);
    }
}