#include "../headers/compiler.hpp"

Compiler::Compiler(std::string sourcePath)
{
    if(IsNotValidPath(sourcePath))
    {
        Output::PrintCustomizeError("Fatal Error: ", "source file not found!");
        exit(EXIT_FAILURE);
    }

    this->lexer = new Lexer(sourcePath);
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

        std::cout << "Debug: " << token->value << " | " << token->type << " | " << token->startpos << " | " << token->endpos << "\n";
    }
}