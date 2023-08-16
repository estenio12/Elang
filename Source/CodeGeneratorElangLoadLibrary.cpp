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
    std::string numToTextInterface      = "std::string numberToText(double __num__);";
    std::string numToTextImplementation = "std::string ProgramLoader::numberToText(double __num__){return std::to_string(__num__);}";
    this->FunctionsInterfaces.push_back(numToTextInterface);
    this->FunctionsImplementations.push_back(numToTextImplementation);

    // # Number to Bool
    std::string numToBoolInterface      = "bool numberToBool(double __num__);";
    std::string numToBoolImplementation = "bool ProgramLoader::numberToBool(double __num__){return __num__ != 0;}";
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
    std::string charToNumberInterface      = "double charToNumber(char __char__);";
    std::string charToNumberImplementation = "double ProgramLoader::charToNumber(char __char__){return static_cast<double>(__char__) - 48;}";
    this->FunctionsInterfaces.push_back(charToNumberInterface);
    this->FunctionsImplementations.push_back(charToNumberImplementation);
    
    // # Char to Bool
    std::string charToBoolInterface      = "bool charToBool(char __char__);";
    std::string charToBoolImplementation = "bool ProgramLoader::charToBool(char __char__){return __char__ != '0';}";
    this->FunctionsInterfaces.push_back(charToBoolInterface);
    this->FunctionsImplementations.push_back(charToBoolImplementation);
}

void CodeGenerator::BooleanConvert()
{
    // # Boolean to Text
    std::string boolToTextInterface      = "std::string boolToText(bool __bool__);";
    std::string boolToTextImplementation = "std::string ProgramLoader::boolToText(bool __bool__){std::string buffer;if(__bool__)buffer=\"true\";else buffer=\"false\";return buffer;}";
    this->FunctionsInterfaces.push_back(boolToTextInterface);
    this->FunctionsImplementations.push_back(boolToTextImplementation);
    
    // # Boolean to Number
    std::string boolToNumberInterface      = "double boolToNumber(bool __bool__);";
    std::string boolToNumberImplementation = "double ProgramLoader::boolToNumber(bool __bool__){return __bool__;}";
    this->FunctionsInterfaces.push_back(boolToNumberInterface);
    this->FunctionsImplementations.push_back(boolToNumberImplementation);
}

void CodeGenerator::TextConvert()
{
    // # Text to Boolean
    std::string textToBoolInterface      = "bool textToBool(std::string __text__);";
    std::string textToBoolImplementation = "bool ProgramLoader::textToBool(std::string __text__){return __text__==\"true\"||__text__==\"TRUE\";}";
    this->FunctionsInterfaces.push_back(textToBoolInterface);
    this->FunctionsImplementations.push_back(textToBoolImplementation);
    
    // # Text to Number
    std::string textToNumberInterface      = "double textToNumber(std::string __text__);";
    std::string textToNumberImplementation = "double ProgramLoader::textToNumber(std::string __text__){try{return std::stold(__text__);}catch(exception& e){std::cerr<<\"DataConvertException: Text content is not valid to conversion.\n\"<<\"Content Error: \"<<__text__;exit(EXIT_FAILURE);}}";
    this->FunctionsInterfaces.push_back(textToNumberInterface);
    this->FunctionsImplementations.push_back(textToNumberImplementation);
}




