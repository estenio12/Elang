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
#include "../Include/IDFunctionDeclarationStorage.hpp"

class CodeGenerator
{   
    private:
        std::string OutputName  = "app.cpp";
        std::ofstream fileHandle;

    private:
        IDDeclarationStorage* IDTable;
        IDFunctionDeclarationStorage* IDFunTable;
        Tools* tool;
        const std::string EMPTY = "";

    private:
        std::vector<std::string> FunctionsInterfaces;
        std::vector<std::string> FunctionsImplementations;
        std::vector<std::string> RunnablePipeline;

    public:
        CodeGenerator(IDDeclarationStorage*, IDFunctionDeclarationStorage* );
        ~CodeGenerator();

    public:
        void Generate(AST );

    private:
        void WriteChunkIntoFile(std::string );
        void CloseFileHandler();
        void WriteInitContent();
        void WriteFullApp();
        void DeleteBranch(AstNode* );
        std::string TransformSpecialCharacter(std::string );

    private:
        void ThrowError(std::string );
        std::string ConvertToString(std::string );
        std::string ConvertToChar(std::string );
        std::string GetTargetType(std::string );
        std::string CreateFunctionInterface(AstNode* );
        std::string CreateFunctionImplementationHeader(AstNode* );
        std::string ExtractParameters(std::string );
        AstNode* FindLastNode(AstNode*, uint8_t );

    private:
        bool generateWithLet = false;
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
        std::string VisitorStatement(std::vector<std::pair<std::string, AstNode*>> );
        std::string CommitStatement();

    private:
        std::vector<std::string> FunctionDeclarationCodeStack;
        std::string GenerateFunctionDeclaration(AstNode* );
        std::string VisitorFunctionDeclaration(AstNode* );
        std::string CommitFunctionDeclaration();

    private:
        std::vector<std::string> AssignmentExpressionCodeStack;
        std::string GenerateAssignmentExpression(AstNode* );
        std::string VisitorAssignmentExpression(AstNode* );
        std::string CommitAssignmentExpression();

    private:
        std::string GenerateCallFunction(AstNode* );

    private:
        std::vector<std::string> ConditionDeclarationCodeStack;
        std::string GenerateConditionDeclaration(AstNode* );
        std::string VisitorConditionDeclaration(AstNode* );
        std::string CommitConditionDeclaration();

    private:
        std::string GenerateCloseStatement(AstNode* );

    private:
        void ElangLoadLibrary();
        void IO_Input();
        void IO_Output();
        void IO_System();

        // # Data Convert
        void DataConvert();
        void NumberConvert();
        void CharacterConvert();
        void BooleanConvert();
        void TextConvert();
};