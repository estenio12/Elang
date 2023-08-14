// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>

namespace FILE_CONTENT
{
    const std::string COMMENTARY              = "// # Code generated by Elang Compiler";
    const std::string INCLUDES                = "#include<bits/stdc++.h>";
    const std::string PROGRAM_INTERFACE       = "class ProgramLoader{public:ProgramLoader();~ProgramLoader();public:void Run();private:";
    const std::string CLOSE_PROGRAM_INTERFACE = "};";
    const std::string PROGRAM_RUNNABLE        = "ProgramLoader::ProgramLoader(){}ProgramLoader::~ProgramLoader(){}void ProgramLoader::Run(){";
    const std::string CLOSE_PROGRAM_RUNNABLE  = "}";
    const std::string PROGRAM_BOOTSTRAP       = "int main(int argc, char* argv[]){auto startup=new ProgramLoader();startup->Run();return EXIT_SUCCESS;}";
    const std::string STANDARD_PROGRAM_NAME   = "ProgramLoader::";
}

namespace TARGET_CODE
{
    static const std::string T_ASSING      = "=";
    static const std::string T_EOL         = ";";
    static const std::string T_OPEN_PARAM  = "(";
    static const std::string T_CLOSE_PARAM = ")";
    static const std::string T_COMMA       = ",";
    static const std::string T_OPEN_BRACE  = "{";
    static const std::string T_CLOSE_BRACE = "}";
    static const std::string T_RETURN      = "return ";
    static const std::string T_IF          = "if";
    static const std::string T_ELSE        = "else";
    static const std::string T_WHILE       = "while";

    static const std::string T_BOOL       = "bool ";
    static const std::string T_FLOAT      = "float ";
    static const std::string T_STRING     = "std::string ";
    static const std::string T_CHAR       = "char ";
    static const std::string T_VOID       = "void ";
}