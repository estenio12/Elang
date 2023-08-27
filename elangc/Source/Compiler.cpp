#include "../Include/Compiler.hpp"

Compiler::Compiler(std::string path)
{
    // # Check if the source code file exists
    this->CheckIfFileExist(path);

    // # Instance Actors
    this->lexer  = new Lexer(path);
    this->parser = new Parser(lexer);
}

Compiler::~Compiler(){}

void Compiler::CheckIfFileExist(std::string path)
{
    if(!std::filesystem::exists(std::filesystem::path(path)))
    {
        Output::PrintCustomizeError("Fatal Error: ", "File cannot be found!");
        exit(EXIT_FAILURE);
    }
}

void Compiler::Run()
{
    this->parser->Parse();
}
