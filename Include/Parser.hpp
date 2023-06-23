// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
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
#include "../Model/Ast.hpp"

class Parser
{
    private:
        AST ast;
        Lexer* lexer;
        Tools* tool;

    private:
        AstNode* buildingNode;
        Token* history;
        int currentBranch;
        int signatureMainBranch;

    // # Arithmetic Variables
    private:
        AstNode* ArithmeticBuildingNode;
        Token* buffer;

        // # OpenParam  ++
        // # CloseParam --
        int relevance = 0;

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
        void AddRelevance();
        void RemoveRelevance();

    private:
        bool VariableDeclaration(Token* );
        void VariableDeclarationCommit();

    private:
        bool ArithmeticOperation(Token* );
        void ArithmeticCommit();
};