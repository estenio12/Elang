// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>
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
        std::vector<Token*> buffer;
        int currentBranch;

    public:
        Parser(Lexer* lexer);
        ~Parser();

    public:
        void Parse();

    private:
        void BindOperation(Token* );

    private:
        void VariableDeclaration(Token* );
};