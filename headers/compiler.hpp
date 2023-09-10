// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <filesystem>
#include "./lexer.hpp"
#include "../helpers/debug-tokens.hpp"
#include "output.hpp"

class Compiler
{
    private:
        Lexer* lexer;
        DebugToken* debug;

    public:
        Compiler(std::string sourcePath);
        ~Compiler();

    public:
        void Run();

    private:
        bool IsNotValidPath(std::string sourcePath);
};