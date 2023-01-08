#include "../Includes/Compiler.hpp"

Compiler::Compiler(char** Path)
{
    this->FilePathSource = Path[1];
    this->FilePathOutput = "./Test/App.html";
}

Compiler::~Compiler(){}

bool Compiler::PathIsRight()
{
    return std::filesystem::exists(
        std::filesystem::path(this->FilePathSource));
}

void Compiler::Run()
{
    if(!PathIsRight())
    {
        Console::PrintError("File cannot be founded! ("+this->FilePathSource+")");
        exit(EXIT_FAILURE);
    }

    Console::Print(this->FilePathSource);
}