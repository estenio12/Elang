#include "../Include/Parser.hpp"

void Parser::ElangLoadLibrary()
{
    this->IO_Input();
    this->IO_Output();
    this->IO_System();
}

void Parser::IO_Input()
{
    // #  READLINE
    auto readline = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_READLINE, TYPE::NAME[TYPE::TTEXT]);
    readline->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(readline);

    // #  READWORD
    auto readword = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_READWORD, TYPE::NAME[TYPE::TTEXT]);
    readword->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(readword);
    
    // #  READCHAR
    auto readchar = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_READCHAR, NAME::CHAR);
    readchar->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(readchar);
}

void Parser::IO_Output()
{
    auto output = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_OUTPUT, TYPE::NAME[TYPE::TVOID]);
    output->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(output);
}

void Parser::IO_System()
{
    auto system = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_SYSTEM, TYPE::NAME[TYPE::TVOID]);
    system->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(system);
}

