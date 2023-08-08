#include "../Include/CodeGenerator.hpp"

CodeGenerator::CodeGenerator(IDDeclarationStorage* IDTable, IDFunctionDeclarationStorage* IDFunTable):IDTable(IDTable), IDFunTable(IDFunTable)
{
    this->fileHandle.open(this->OutputName, std::ios::out | std::ios::ate);
    this->tool = new Tools();
    this->WriteInitContent();
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
            this->RunnablePipeline.push_back(chunk);
        }

        // # Generate target code for variable declaration
        if(branch.first == BRANCH_NAME::FUNCTION_DECLARATION)
        {
            this->GenerateFunctionDeclaration(branch.second);
        }

        // # Generate target code for assignment expression
        if(branch.first == BRANCH_NAME::ASSIGNMENT_EXPRESSION)
        {
            auto chunk = this->GenerateAssignmentExpression(branch.second);
            this->RunnablePipeline.push_back(chunk);
        }

        // # Generate target code for call function
        if(branch.first == BRANCH_NAME::CALL_FUNCTION)
        {
            auto chunk = this->GenerateCallFunction(branch.second);
            this->RunnablePipeline.push_back(chunk);
        }

        // # Generate target code for condition declaration
        if(branch.first == BRANCH_NAME::CONDITION_DECLARATION)
        {
            auto chunk = this->GenerateConditionDeclaration(branch.second);
            this->RunnablePipeline.push_back(chunk);
        }

        // # Generate target code for close statement
        if(branch.first == BRANCH_NAME::CLOSE_STATEMENT)
        {
            auto chunk = this->GenerateCloseStatement(branch.second);
            this->RunnablePipeline.push_back(chunk);
        }
    }

    this->WriteFullApp();
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
    return "\"" + value + "\"";
}

std::string CodeGenerator::ConvertToChar(std::string value)
{
    return "'" + value + "'";
}

void CodeGenerator::WriteInitContent()
{
    this->WriteChunkIntoFile(FILE_CONTENT::COMMENTARY + "\n");
    this->WriteChunkIntoFile(FILE_CONTENT::INCLUDES   + "\n");
    this->WriteChunkIntoFile(FILE_CONTENT::PROGRAM_INTERFACE);
}

void CodeGenerator::WriteFullApp()
{
    // # Write interface
    for(auto item : this->FunctionsInterfaces)
        this->WriteChunkIntoFile(item);

    // # Close interface statement
    this->WriteChunkIntoFile(FILE_CONTENT::CLOSE_PROGRAM_INTERFACE + "\n");

    // # Write runnable
    this->WriteChunkIntoFile(FILE_CONTENT::PROGRAM_RUNNABLE);

    for(auto item : this->RunnablePipeline)
        this->WriteChunkIntoFile(item);

    // # Close runnable statement
    this->WriteChunkIntoFile(FILE_CONTENT::CLOSE_PROGRAM_RUNNABLE + "\n");

    // # Write function implementation
    for(auto item : this->FunctionsImplementations)
        this->WriteChunkIntoFile(item);
    
    // # Break line
    this->WriteChunkIntoFile("\n");

    // # Write program startup
    this->WriteChunkIntoFile(FILE_CONTENT::PROGRAM_BOOTSTRAP);
}

std::string CodeGenerator::GetTargetType(std::string value)
{
    if(value == TYPE::NAME[TYPE::TBOOL]) return TARGET_CODE::T_BOOL;
    if(value == TYPE::NAME[TYPE::TNUMBER]) return TARGET_CODE::T_FLOAT;
    if(value == TYPE::NAME[TYPE::TCHAR]) return TARGET_CODE::T_CHAR;
    if(value == TYPE::NAME[TYPE::TTEXT]) return TARGET_CODE::T_STRING;
    if(value == TYPE::NAME[TYPE::TVOID]) return TARGET_CODE::T_VOID;

    this->ThrowErro("GetTargetType not found a valid type!");
    return EMPTY;
}

std::string CodeGenerator::CreateFunctionInterface(AstNode* node)
{
    auto typeFunction = this->GetTargetType(node->parent->token->value);
    auto nameFunction = node->token->value;
    auto result = typeFunction + 
                  nameFunction + 
                  TARGET_CODE::T_OPEN_PARAM +
                  this->ExtractParameters(nameFunction) +
                  TARGET_CODE::T_CLOSE_PARAM +
                  TARGET_CODE::T_EOL;

    return result;
}

std::string CodeGenerator::CreateFunctionImplementationHeader(AstNode* node)
{
    auto typeFunction = this->GetTargetType(node->parent->token->value);
    auto nameFunction = node->token->value;
    auto result = typeFunction + 
                  FILE_CONTENT::STANDARD_PROGRAM_NAME +
                  nameFunction + 
                  TARGET_CODE::T_OPEN_PARAM +
                  this->ExtractParameters(nameFunction) +
                  TARGET_CODE::T_CLOSE_PARAM;

    return result;
}

std::string CodeGenerator::ExtractParameters(std::string funID)
{
    auto getEntity = this->IDFunTable->FindObjectIdentifier(funID);

    if(getEntity != nullptr)
    {
        std::string buildParameter;
        bool isFirstPass = true;

        for(auto item : getEntity->paramList)
        {
            if(isFirstPass) 
                isFirstPass = false;
            else
                buildParameter.push_back(',');

            buildParameter += this->GetTargetType(item.first);
            buildParameter += item.second;
        }

        return buildParameter;
    }

    return EMPTY;
}

AstNode* CodeGenerator::FindLastNode(AstNode* node, uint8_t direction)
{
    if(node == nullptr) return nullptr;

    if(direction == AST_DIRECTION::LEFT)
    {
        if(node->HasLeftNode())
           return this->FindLastNode(node->left, direction);
    
        return node;
    }
    else
    {
        if(node->HasRightNode())
           return this->FindLastNode(node->right, direction);
    
        return node;
    }
}


