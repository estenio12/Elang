#include "../Include/Parser.hpp"

void Parser::ElangLoadLibrary()
{
    this->IO_Input();
    this->IO_Output();
    this->IO_System();
    this->DataConvert();
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

void Parser::DataConvert()
{
    this->NumberConvert();
    this->CharacterConvert();
    this->BooleanConvert();
    this->TextConvert();
}

void Parser::NumberConvert()
{
    // # Number to Text
    auto numberToText = this->IDFunTable->CreateRow(DATA_CONVERT::NUM_TO_TEXT, NAME::TEXT);
    numberToText->paramList.push_back(std::make_pair(NAME::NUMBER, "__param"));
    this->IDFunTable->InsertFunctionID(numberToText);
    
    // # Number to Bool
    auto numberToBool = this->IDFunTable->CreateRow(DATA_CONVERT::NUM_TO_BOOL, NAME::BOOLEAN);
    numberToBool->paramList.push_back(std::make_pair(NAME::NUMBER, "__param"));
    this->IDFunTable->InsertFunctionID(numberToBool);
}

void Parser::CharacterConvert()
{
    // # Char to Text
    auto charToText = this->IDFunTable->CreateRow(DATA_CONVERT::CHAR_TO_TEXT, NAME::TEXT);
    charToText->paramList.push_back(std::make_pair(NAME::CHAR, "__param"));
    this->IDFunTable->InsertFunctionID(charToText);
    
    // # Char to Number
    auto charToNumber = this->IDFunTable->CreateRow(DATA_CONVERT::CHAR_TO_NUM, NAME::NUMBER);
    charToNumber->paramList.push_back(std::make_pair(NAME::CHAR, "__param"));
    this->IDFunTable->InsertFunctionID(charToNumber);
    
    // # Char to Bool
    auto charToBool = this->IDFunTable->CreateRow(DATA_CONVERT::CHAR_TO_BOOL, NAME::BOOLEAN);
    charToBool->paramList.push_back(std::make_pair(NAME::CHAR, "__param"));
    this->IDFunTable->InsertFunctionID(charToBool);
}

void Parser::BooleanConvert()
{
    // # Boolean to Text
    auto boolToText = this->IDFunTable->CreateRow(DATA_CONVERT::BOOL_TO_TEXT, NAME::TEXT);
    boolToText->paramList.push_back(std::make_pair(NAME::BOOLEAN, "__param"));
    this->IDFunTable->InsertFunctionID(boolToText);
    
    // # Boolean to Number
    auto boolToNumber = this->IDFunTable->CreateRow(DATA_CONVERT::BOOL_TO_NUM, NAME::NUMBER);
    boolToNumber->paramList.push_back(std::make_pair(NAME::BOOLEAN, "__param"));
    this->IDFunTable->InsertFunctionID(boolToNumber);
}

void Parser::TextConvert()
{
    // # Text to Boolean
    auto textToBool = this->IDFunTable->CreateRow(DATA_CONVERT::TEXT_TO_BOOL, NAME::BOOLEAN);
    textToBool->paramList.push_back(std::make_pair(NAME::TEXT, "__param"));
    this->IDFunTable->InsertFunctionID(textToBool);
    
    // # Text to Number
    auto textToNumber = this->IDFunTable->CreateRow(DATA_CONVERT::TEXT_TO_NUM, NAME::NUMBER);
    textToNumber->paramList.push_back(std::make_pair(NAME::TEXT, "__param"));
    this->IDFunTable->InsertFunctionID(textToNumber);
}




