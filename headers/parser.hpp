// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "lexer.hpp"
#include "../models/ast.hpp"
#include "../definitions/token-definition.hpp"
#include "../helpers/debug-compiler.hpp"

class Parser
{
    public:
        Lexer* lexer;
        DebugCompiler* debug;

    public:
        Parser(Lexer* lexer);
        ~Parser();

    public:
        void Parse();

    private:    
        BRANCH_TYPE BindOperation(Token*);
        void ExpectType(TYPE_TOKEN, std::string message);
        void ExpectValue(std::string, std::string message);
        void ThrowError(Token*, std::string message);
        void ThrowInternalError(std::string message);
        void PushToAst(AstBranch* node);

    private:
        template<class T> void CheckMemoryAllocated(T entity)
        {
            if(entity == nullptr) 
            {
                Output::PrintCustomizeError("Fatal Error: ", "Out of Memory");
                exit(EXIT_FAILURE);
            }
        }
        
    private:
        bool IsVariableDeclaration(Token*);

    private:
        AstBranch* BuildVariableDeclaration(Token*);
};