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
#include "../Helpers/Tools.hpp"
#include "../Include/Output.hpp"
#include "../Include/IDDeclarationStorage.hpp"

class CodeGenerator
{   
    private:
        std::string OutputName  = "app.js";
        std::ofstream fileHandle;

    private:
        IDDeclarationStorage* IDTable;
        Tools* tool;
        std::vector<std::string> CodeStack;
        int oldOperation = BRANCH_IDENTIFIER::UNDEFINED;
        const std::string EMPTY = "";

    public:
        CodeGenerator(IDDeclarationStorage* );
        ~CodeGenerator();

    public:
        void Generate(AST );

    private:
        void WriteChunkIntoFile(std::string );
        void CloseFileHandler();

    private:
        void ThrowErro(std::string );
        std::string AddWhitespace(std::string );
        std::string ConvertToString(std::string );

    private:
        std::vector<std::string> VariableDeclarationCodeStack;
        std::string VariableDeclarationCurrentType;
        std::string GenerateVariableDeclaration(AstNode* );
        std::string VisitorVariableDeclaration(AstNode* );
        std::string CommitVariableDeclaration();

    private:
        std::vector<std::string> ExpressionCodeStack;
        std::string VisitorExpression(AstNode* );
        std::string CommitExpression();

    private:
        std::vector<std::string> StatementCodeStack;
        std::string VisitorStatement(AstNode* );
        std::string CommitStatement();

    private:
        std::vector<std::string> FunctionDeclarationCodeStack;
        std::string GenerateFunctionDeclaration(AstNode* );
        std::string VisitorFunctionDeclaration(AstNode* );
        std::string CommitFunctionDeclaration();
};