// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"

class CodeGenerator
{   
    private:
        std::string OutputName  = "app.html";
        std::fstream fileHandle; 

    public:
        CodeGenerator();
        ~CodeGenerator();

    public:
        void Generate(AST );

    private:
        void GenerateVariableDeclaration();

};