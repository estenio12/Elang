// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include "../Helpers/Tools.hpp"
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Include/Output.hpp"
#include "../Include/LexicalAnalyser.hpp"
#include "../Include/IDDeclarationStorage.hpp"
#include "../Model/Ast.hpp"
#include "../Include/CodeGenerator.hpp"

class Parser
{
    private:
        AST ast;
        Lexer* lexer;
        Tools* tool;
        IDDeclarationStorage* IDTable;
        CodeGenerator* codegen;

    private:
        AstNode* buildingNode;
        Token* history;
        int currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
        int oldOperation  = BRANCH_IDENTIFIER::UNDEFINED;
        std::string expectedType = EXPECTED_TYPE::TUNDEFINED;
        std::string currentScope = STANDARD_SCOPE_NAME::GLOBALSCOPE;
        int currentDeep = 0;
        bool isConstant = false;

    // # Arithmetic Variables
    private:
        AstNode* ArithmeticBuildingNode;
        // # OpenParam  ++
        // # CloseParam --
        int paremCounter = 0;

    public:
        Parser(Lexer* lexer);
        ~Parser();

    public:
        void Parse();

    private:
        void ThrowError(std::string, int);
        void ThrowError(Token* );
        void ResetState();

    private:
        void IdentifyOperationType(Token* );
        void AssignCurrentBranch(uint8_t );
        void InsertAstNode(std::string, AstNode* );
        void InsertBuildingNode(Token*, uint8_t );
        AstNode* FindLastNode(AstNode*, uint8_t );
        void InsertBuffer(Token* );
        Token* ConsumeNextTokenFromBuffer();
        void AddParemCounter();
        void RemoveParemCounter();

    private:
        bool VariableDeclaration(Token* );
        void VariableDeclarationCommit();
        std::string GetTypeVariableDeclaration(Token* );

    private:
        // std::vector<std::string> ArithmeticStack;
        bool ArithmeticOperation(Token* );
        bool ArithmeticOperationCheckOpenParam(Token* );
        bool ArithmeticOperationCheckType(Token* );
        bool ArithmeticOperationCheckIdentifier(Token* );
        void InsertArithmeticNode(Token*, int );
        void ArithmeticCommit();
};