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

    private:
        std::string OutputFileName = "MyApplication.cpp";

    public:
        Compiler(std::string sourcePath);
        ~Compiler();

    public:
        void Run();

    private:
        void DeleteExistsFile();
        bool IsNotValidPath(std::string sourcePath);
};