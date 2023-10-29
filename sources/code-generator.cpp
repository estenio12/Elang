#include "../headers/code-generator.hpp"

CodeGenerator::CodeGenerator()
{
    this->fileHandler.open(this->OutputFileName, std::ios::out | std::ios::app);
    this->LoadProgramInitialize();
}

CodeGenerator::~CodeGenerator()
{
    this->FunctionInterface.clear();
    this->FunctionImplementation.clear();
    this->RunnableImplementation.clear();
}

void CodeGenerator::Run(Ast* ast)
{
    Output::Print("Entrei");
    
    // # Flush code resultant to file
    this->FlushFunctionInterfaceToFile();
    this->FlushRunnableImplementationToFile();
    this->FlushFunctionImplementationToFile();
    this->WriteChunkToFile(this->PROGRAM_BOOTSTRAP);

    // # Close file stream
    this->fileHandler.close();
}

void CodeGenerator::WriteChunkToFile(std::string chunk)
{
    if(!chunk.empty())
        this->fileHandler.write(chunk.c_str(), chunk.size());
}

void CodeGenerator::LoadProgramInitialize()
{
    this->WriteChunkToFile(this->COMMENTARY);
    this->WriteChunkToFile(this->INCLUDES);
    this->WriteChunkToFile(this->PROGRAM_INTERFACE);
}

void CodeGenerator::FlushFunctionInterfaceToFile()
{
    std::string buffer;

    for(auto item : this->FunctionInterface)
        buffer += item;

    this->WriteChunkToFile(buffer);
    this->WriteChunkToFile(this->CLOSE_PROGRAM_INTERFACE);
    buffer.clear();
    this->FunctionInterface.clear();
}

void CodeGenerator::FlushFunctionImplementationToFile()
{
    std::string buffer;

    for(auto item : this->FunctionImplementation)
        buffer += item;

    this->WriteChunkToFile(buffer);
    buffer.clear();
    this->FunctionImplementation.clear();
}

void CodeGenerator::FlushRunnableImplementationToFile()
{
    std::string buffer;
    this->WriteChunkToFile(this->PROGRAM_RUNNABLE);

    for(auto item : this->RunnableImplementation)
        buffer += item;

    this->WriteChunkToFile(buffer);
    this->WriteChunkToFile(this->CLOSE_PROGRAM_RUNNABLE);
    buffer.clear();
    this->RunnableImplementation.clear();
}



