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
#include <filesystem>
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/TargetCodeDictionary.hpp"
#include "../Include/Output.hpp"
#include "../Include/IDDeclarationStorage.hpp"

class CodeGenerator
{   
    private:
        std::string OutputName  = "app.js";
        std::ofstream fileHandle;

    private:
        IDDeclarationStorage* IDTable;
        std::vector<std::string> CodeStack;

    public:
        CodeGenerator(IDDeclarationStorage* );
        ~CodeGenerator();

    public:
        void Generate(AST );

    private:
        void WriteOutputFile();

    private:
        void ThrowErro(std::string );
        std::string AddWhitespace(std::string );
        std::string FormatString(std::string );

    private:
        std::vector<std::string> VariableDeclarationCodeStack;
        std::string VariableDeclarationCurrentType;
        void GenerateVariableDeclaration(AstNode* );
        void VisitorVariableDeclaration(AstNode* );
        void CommitVariableDeclaration();
};