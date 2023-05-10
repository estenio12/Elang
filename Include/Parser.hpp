// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>
#include "../Helpers/Tools.hpp"
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Include/Output.hpp"
#include "../Include/Ast.hpp"
#include "../Include/LexicalAnalyser.hpp"

class Parser
{
    private:
        AST ast;
        // SyntaxPatternMatch* syntax
        Lexer* lexer;

    private:
        int* lineCounter;

    private:
        AstNode* buildingNode;

    public:
        Parser(Lexer* lexer);
        ~Parser();

    public:
        void Parse();

    private:
        
};