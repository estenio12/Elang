#include "../Include/CodeGenerator.hpp"

CodeGenerator::CodeGenerator(IDDeclarationStorage* IDTable):IDTable(IDTable)
{
    this->fileHandle.open(this->OutputName, std::ios::out);
}

CodeGenerator::~CodeGenerator(){}

void CodeGenerator::Generate(AST ast)
{
    for(auto branch : ast)
    {
        // # Generate target code for variable declaration
        if(branch.first == BRANCH_NAME::VARIABLE_DECLARATION)
           this->GenerateVariableDeclaration(branch.second);
    }

    this->WriteOutputFile();
}

void CodeGenerator::ThrowErro(std::string message)
{
    Output::PrintCustomizeError("Code Generator error: ", message);
    exit(EXIT_FAILURE);
}

std::string CodeGenerator::AddWhitespace(std::string value)
{
    return " " + value;
}

void CodeGenerator::CheckFileExist()
{
    auto path = std::filesystem::path(this->OutputName);
    if(std::filesystem::exists(path)) std::filesystem::remove(path);
}

void CodeGenerator::WriteOutputFile()
{
    this->CheckFileExist();

    // this->fileHandle.write();
}


