// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "./lexer.hpp"

class Compiler
{
    private:
        Lexer* lexer;

    public:
        Compiler(std::string sourcePath);
        ~Compiler();

    public:
        void Run();
};