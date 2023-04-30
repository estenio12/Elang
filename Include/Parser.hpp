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
#include "../Include/SyntaxPatternMatch.hpp"
#include "../Include/Output.hpp"
#include "../Include/Ast.hpp"

class Parser
{
    private:
        AST ast;
        SyntaxPatternMatch* syntax;

    private:
        int* lineCounter;
        bool AstReady = false;

    private:
        token_list buildPattern;

    // # States
    private:
        const int globalscope = 0;
        int currentscope = globalscope;

    public:
        Parser(int* lineCounter);
        ~Parser();

    public:
        bool Parse(token_list );

    private:
        void ResetBuildPattern();
        bool IsTerminateCharacter(token );
        void PatternMatch();
};