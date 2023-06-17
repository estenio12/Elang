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

    private:
        int* lineCounter;

    private:
        AstNode* buildingNode;
        Token* history;
        std::vector<Token*> buffer;
        int currentBranch;

    public:
        Parser(Lexer* lexer);
        ~Parser();

    public:
        void Parse();

    private:
        void ThrowError(std::string, int);
        void ResetState();

    private:
        void BindOperation(Token* );
        void InsertAstNode(std::string, AstNode* );
        void InsertBuildingNode(Token*, uint8_t );
        AstNode* FindLastNode(AstNode*, uint8_t );

    private:
        bool VariableDeclaration(Token* );
        void VariableDeclarationCommit();
};