#include "../Includes/Compiler.hpp"

Compiler::Compiler(char** Path)
{
    this->Path = Path[0];
}

Compiler::~Compiler(){}

bool Compiler::PathIsRight()
{
    return std::filesystem::exists(
        std::filesystem::path(this->Path));
}