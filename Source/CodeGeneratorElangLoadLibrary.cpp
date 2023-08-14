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
    std::string interface      = "void print(std::string);";
    std::string implementation = "void ProgramLoader::print(std::string __text__){std::cout<<__text__;}";
    this->FunctionsInterfaces.push_back(interface);
    this->FunctionsImplementations.push_back(implementation);
}

void CodeGenerator::IO_System()
{
    std::string interface      = "void sysexec(std::string);";
    std::string implementation = "void ProgramLoader::sysexec(std::string __text__){system(__text__.c_str());}";
    this->FunctionsInterfaces.push_back(interface);
    this->FunctionsImplementations.push_back(implementation);
}