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
#include "../models/ast.hpp"

class CodeGenerator
{
    private:
        std::vector<std::string> FunctionInterface;
        std::vector<std::string> FunctionImplementation;
        std::vector<std::string> GlobalDeclaration;

    public:
        CodeGenerator();
        ~CodeGenerator();

    public:
        void Run(Ast* ast);

    private:
        
};