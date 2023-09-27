// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <cstdint>
#include "lexer.hpp"
#include "../models/ast.hpp"
#include "../models/expression.hpp"
#include "../models/symbol-table.hpp"
#include "../definitions/token-definition.hpp"
#include "../helpers/debug-compiler.hpp"

class Parser
{
    public:
        Lexer* lexer;
        DebugCompiler* debug;
        SymbolTable* symbolTable;
        Ast* ast;

    public:
        const std::string GLOBAL_SCOPE = "GLOBAL"; 
        std::string currentScope = GLOBAL_SCOPE;
        int currentDeep = 0;

    public:
        Parser(Lexer* lexer, SymbolTable*, Ast*);
        ~Parser();

    public:
        void Parse();

    private:    
        EBRANCH_TYPE BindOperation(Token*);
        void ExpectType(TYPE_TOKEN, std::string message);
        void ExpectValue(std::string, std::string message);
        void ThrowError(Token*, std::string message);
        void ThrowInternalError(std::string message);
        void PushToAst(AstBranch* node);
        void InsertIdentifierIntoSymbolTable(AstBranch*);

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

    private:
        Expression* BuildExpression();
        BinaryOperation* ParserExpression(Tokens* tokenList, Expression* expr, uint8_t minPrecedence);
        BinaryOperation* ParserPrimary(Tokens* tokenList, Expression* expr);
        uint8_t GetPrecedenceValue(Token*);

};