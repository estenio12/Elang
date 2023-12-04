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
#include "code-generator.hpp"

#include "../models/symbol-table.hpp"

class Compiler
{
    private:
        Lexer* lexer;
        Parser* parser;
        Ast* ast;
        SymbolTable* symbolTable;
        CodeGenerator* codegen;

    public:
        Compiler(std::string sourcePath, std::string outputFileName);
        ~Compiler();

    public:
        void Run();

    private:
        bool IsNotValidPath(std::string sourcePath);
};