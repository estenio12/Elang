#include "../Include/CodeGenerator.hpp"

void CodeGenerator::ElangLoadLibrary()
{
    this->IO_Input();
    this->IO_Output();
    this->IO_System();
}

void CodeGenerator::IO_Input()
{
    std::string readLineInterface = "std::string readline(std::string);";
    std::string readWordInterface = "std::string readword(std::string);";
    std::string readCharInterface = "const char readchar(std::string);";

    std::string readLineImplementation = "std::string ProgramLoader::readline(std::string __text__=\"\"){std::string buffer;if(!__text__.empty())std::cout<<__text__;std::getline(std::cin,buffer);return buffer;}";
    std::string readWordImplementation = "std::string ProgramLoader::readword(std::string __text__=\"\"){std::string buffer;if(!__text__.empty())std::cout<<__text__;std::cin >> buffer;return buffer;}";
    std::string readCharImplementation = "const char ProgramLoader::readchar(std::string __text__=\"\"){std::string buffer;if(!__text__.empty())std::cout<<__text__;std::cin >> buffer;return buffer[0];}";
    
    this->FunctionsInterfaces.push_back(readLineInterface);
    this->FunctionsInterfaces.push_back(readWordInterface);
    this->FunctionsInterfaces.push_back(readCharInterface);

    this->FunctionsImplementations.push_back(readLineImplementation);
    this->FunctionsImplementations.push_back(readWordImplementation);
    this->FunctionsImplementations.push_back(readCharImplementation);
}

void CodeGenerator::IO_Output()
{
    std::string printInterface = "void print(std::string);";
    std::string implementation = "void ProgramLoader::print(std::string __text__){std::cout<<__text__;}";
    this->FunctionsInterfaces.push_back(printInterface);
    this->FunctionsImplementations.push_back(implementation);
}

void CodeGenerator::IO_System()
{
    std::string sysexecInterface = "void sysexec(std::string);";
    std::string implementation   = "void ProgramLoader::sysexec(std::string __text__){system(__text__.c_str());}";
    this->FunctionsInterfaces.push_back(sysexecInterface);
    this->FunctionsImplementations.push_back(implementation);
}

void CodeGenerator::DataConvert()
{
    this->NumberConvert();
    this->CharacterConvert();
    this->BooleanConvert();
    this->TextConvert();
}

void CodeGenerator::NumberConvert()
{
    // # Number to Text
    std::string numToTextInterface      = "std::string numToText(double __num__);";
    std::string numToTextImplementation = "std::string ProgramLoader::numToText(double __num__){return std::to_string(__num__);}";
    this->FunctionsInterfaces.push_back(numToTextInterface);
    this->FunctionsImplementations.push_back(numToTextImplementation);

    // # Number to Bool
    std::string numToBoolInterface      = "bool numToBool(double __num__);";
    std::string numToBoolImplementation = "bool ProgramLoader::numToBool(double __num__){return __num__ != 0;}";
    this->FunctionsInterfaces.push_back(numToBoolInterface);
    this->FunctionsImplementations.push_back(numToBoolImplementation);
}

void CodeGenerator::CharacterConvert()
{
    // # Char to Text
    std::string charToTextInterface      = "std::string charToText(char __num__);";
    std::string charToTextImplementation = "std::string ProgramLoader::charToText(char __char__){std::string buffer{__char__}; return buffer;}";
    this->FunctionsInterfaces.push_back(charToTextInterface);
    this->FunctionsImplementations.push_back(charToTextImplementation);
    
    // # Char to Number
    
    
    // # Char to Bool
    
}

void CodeGenerator::BooleanConvert()
{
    // # Boolean to Text
    
    
    // # Boolean to Number
    
    
    // # Boolean to Char
    
}

void CodeGenerator::TextConvert()
{
    // # Text to Boolean
    
    
    // # Text to Number
    
}




