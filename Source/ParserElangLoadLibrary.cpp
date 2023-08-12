#include "../Include/Parser.hpp"

void Parser::ElangLoadLibrary()
{
    this->IO_Input();
    this->IO_Output();
    this->IO_System();
}

void Parser::IO_Input()
{
    auto input = this->IDFunTable->CreateRow(SYSTEM_CALL::IO_INPUT, TYPE::NAME[TYPE::TTEXT]);
    input->paramList.push_back(std::make_pair("text", "__param"));
    this->IDFunTable->InsertFunctionID(input);
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

