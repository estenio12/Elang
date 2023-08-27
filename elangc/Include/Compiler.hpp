// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "../Include/LexicalAnalyser.hpp"
#include "../Include/Parser.hpp"
#include "../Include/Output.hpp"
#include "../Helpers/Tools.hpp"

class Compiler
{
    private:
        int lineCounter = 0;

    private:
        Lexer* lexer;
        Parser* parser;

    public:
        Compiler(std::string path);
        ~Compiler();

    public:
        void Run();

    private:
        void CheckIfFileExist(std::string path);
};