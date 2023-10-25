#include "../headers/code-generator.hpp"

CodeGenerator::CodeGenerator()
{
    this->fileHandler.open(this->OutputFileName, std::ios::app);
}

CodeGenerator::~CodeGenerator()
{
    this->FunctionInterface.clear();
    this->FunctionImplementation.clear();
    this->GlobalDeclaration.clear();
}

void CodeGenerator::Run(Ast* ast)
{
    
}

void CodeGenerator::WriteChunkToFile(std::string& chunk)
{
    if(!chunk.empty())
        this->fileHandler.write(chunk.c_str(), chunk.size());
}


