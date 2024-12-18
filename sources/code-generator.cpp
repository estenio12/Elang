#include "../headers/code-generator.hpp"

CodeGenerator::CodeGenerator(std::string outputFileName)
{
    if(!outputFileName.empty())
        this->OutputFileName = outputFileName;

    this->DeleteExistsFile();
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
    // # Walk through the AST
    this->AstVisitor(ast);
    
    // # Flush code resultant to file
    this->FlushGlobalDeclarationToFile();
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
        this->fileHandler << chunk;
}

void CodeGenerator::LoadProgramInitialize()
{
    this->WriteChunkToFile(this->COMMENTARY);
    this->WriteChunkToFile(this->LICENSE);
    this->WriteChunkToFile(this->INCLUDES);
    this->WriteChunkToFile(this->LIBRARY_LANG_1);
    this->WriteChunkToFile(this->LIBRARY_LANG_2);
    this->WriteChunkToFile(this->LIBRARY_LANG_3);
    this->WriteChunkToFile(this->LIBRARY_LANG_4);
    this->WriteChunkToFile(this->LIBRARY_LANG_5);
    this->WriteChunkToFile(this->LIBRARY_LANG_6);
    this->WriteChunkToFile(this->LIBRARY_LANG_7);
    this->WriteChunkToFile(this->LIBRARY_LANG_8);
    this->WriteChunkToFile(this->LIBRARY_LANG_9);
    this->WriteChunkToFile(this->LIBRARY_LANG_10);
    this->WriteChunkToFile(this->LIBRARY_LANG_11);
    this->WriteChunkToFile(this->LIBRARY_LANG_12);
    this->WriteChunkToFile(this->LIBRARY_LANG_13);
    this->WriteChunkToFile(this->LIBRARY_LANG_14);
    this->WriteChunkToFile(this->GLOBAL_VARAIBLES);
}

void CodeGenerator::FlushGlobalDeclarationToFile()
{
    std::string buffer;

    for(auto item : this->GlobalVariables)
        buffer += item;

    this->WriteChunkToFile(buffer);
    buffer.clear();
    this->GlobalVariables.clear();
}

void CodeGenerator::FlushFunctionInterfaceToFile()
{
    std::string buffer;

    for(auto item : this->FunctionInterface)
        buffer += item;

    this->WriteChunkToFile(this->PROGRAM_INTERFACE);
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

void CodeGenerator::DeleteExistsFile()
{
    auto path = std::filesystem::path(this->OutputFileName);

    if(std::filesystem::exists(path))
        std::filesystem::remove(path);
}

void CodeGenerator::AstVisitor(Ast* ast)
{
    while(ast->HasContent())
    {
        // # Pega uma branch para processar, ao mesmo tempo 
        // # que remove ela AST para ser processada novamente.
        auto branch = ast->ConsumeBranch();

        // # Verifica se é uma branch válida.
        if(branch != nullptr)
        {
            // # Identifica qual o tipo da branch e aplica a 
            // # geração de código correspondente.
            switch (branch->entity->kind)
            {
                case EBRANCH_TYPE::VARIABLE_DECLARATION:
                    this->GenerateVaraibleDeclaration(branch);
                break;
                case EBRANCH_TYPE::CALL_FUNCTION:
                    this->RunnableImplementation.push_back(branch->entity->GetByteCode() + ';');
                break;

                case EBRANCH_TYPE::FUNCTION_DECLARATION:
                   this->GenerateFunction(branch);
                break;

                case EBRANCH_TYPE::ASSIGNMENT:
                   this->RunnableImplementation.push_back(branch->entity->GetByteCode());
                break;

                case EBRANCH_TYPE::WHILE_DECLARATION:
                   this->RunnableImplementation.push_back(branch->entity->GetByteCode());
                break;

                case EBRANCH_TYPE::IF_ELSE_CONDITION:
                   this->RunnableImplementation.push_back(branch->entity->GetByteCode());
                break;
            }
        }

        MemTools::FreeObjectFromMemory(branch);
    }
}

void CodeGenerator::GenerateFunction(AstBranch* branch)
{
    // # Generate interface
    this->FunctionInterface.push_back(branch->entity->GetInterface());

    // # Generate implementation
    this->FunctionImplementation.push_back(branch->entity->GetByteCode());
}

void CodeGenerator::GenerateVaraibleDeclaration(AstBranch* branch)
{
    auto output_code = branch->entity->GetByteCode();

    if(branch->IsGlobalScope)
        this->GlobalVariables.push_back(output_code);
    else
        this->RunnableImplementation.push_back(output_code);
}




