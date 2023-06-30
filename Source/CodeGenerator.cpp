#include "../Include/CodeGenerator.hpp"

CodeGenerator::CodeGenerator(IDDeclarationStorage* IDTable):IDTable(IDTable)
{
    this->fileHandle.open(this->OutputName, std::ios::out | std::ios::ate);

    this->tool = new Tools();
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

void CodeGenerator::WriteOutputFile()
{
    for(auto item : this->CodeStack)
        this->fileHandle << item;

    this->fileHandle.close();
    this->CodeStack.clear();
    Output::PrintSuccess("Successfully compiled!");
}

std::string CodeGenerator::ConvertToString(std::string value)
{
    return "'" + value + "'";
}


