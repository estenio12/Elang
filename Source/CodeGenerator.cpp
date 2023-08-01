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
        {
            auto chunk = this->GenerateVariableDeclaration(branch.second);
            this->WriteChunkIntoFile(chunk);
        }

        // # Generate target code for variable declaration
        if(branch.first == BRANCH_NAME::FUNCTION_DECLARATION)
        {
            auto chunk = this->GenerateFunctionDeclaration(branch.second);
            this->WriteChunkIntoFile(chunk);
        }

        // # Generate target code for assignment expression
        if(branch.first == BRANCH_NAME::ASSIGNMENT_EXPRESSION)
        {
            auto chunk = this->GenerateAssignmentExpression(branch.second);
            this->WriteChunkIntoFile(chunk);
        }

        // # Generate target code for call function
        if(branch.first == BRANCH_NAME::CALL_FUNCTION)
        {
            auto chunk = this->GenerateCallFunction(branch.second);
            this->WriteChunkIntoFile(chunk);
        }
    }

    this->CloseFileHandler();
}

void CodeGenerator::ThrowErro(std::string message)
{
    Output::PrintCustomizeError("Code Generator error: ", message);
    exit(EXIT_FAILURE);
}

void CodeGenerator::WriteChunkIntoFile(std::string chunk)
{
    this->fileHandle << chunk;
}

void CodeGenerator::CloseFileHandler()
{
    this->fileHandle.close();
}

std::string CodeGenerator::ConvertToString(std::string value)
{
    return "'" + value + "'";
}


