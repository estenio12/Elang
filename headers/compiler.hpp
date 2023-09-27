// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <filesystem>
#include "lexer.hpp"
#include "output.hpp"
#include "parser.hpp"

#include "../models/symbol-table.hpp"

class Compiler
{
    private:
        Lexer* lexer;
        Parser* parser;
        SymbolTable* symbolTable;
        Ast* ast;

    public:
        Compiler(std::string sourcePath);
        ~Compiler();

    public:
        void Run();

    private:
        bool IsNotValidPath(std::string sourcePath);
};