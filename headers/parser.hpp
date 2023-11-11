// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <cstdint>
#include <functional>
#include <chrono>
#include <vector>
#include <stack>
#include "lexer.hpp"
#include "../models/ast.hpp"
#include "../models/expression.hpp"
#include "../models/symbol-table.hpp"
#include "../definitions/token-definition.hpp"

class Parser
{
    private:
        Lexer* lexer;
        SymbolTable* symbolTable;
        Ast* ast;

    private:
        const int GLOBAL_DEEP          = 0; 
        const std::string GLOBAL_SCOPE = "GLOBAL"; 
        std::string currentScope       = GLOBAL_SCOPE;
        int currentDeep                = 0;

    private:
        int lineHistory = 0;

    public:
        Parser(Lexer* lexer, SymbolTable*, Ast*);
        ~Parser();

    public:
        Ast* Parse();

    private:    
        EBRANCH_TYPE BindOperation(Token*);
        void ExpectType(TYPE_TOKEN, std::string message);
        void ExpectValue(std::string expected, std::string message);
        void ThrowError(Token*, std::string message);
        void ThrowInternalError(std::string message);
        void PushToAst(AstBranch* node);
        void InsertIdentifierIntoSymbolTable(VariableDeclaration*);
        Token* GetNextToken(std::string msg);
        std::string GenerateCallFunctionHash();
        std::vector<Tokens*> GetNewInstanceOfArgumentList(int ArgumentSize);
        void CheckIdentifier(Token* token);

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
        bool IsFunctionDeclaration(Token*);
        bool IsReturnExpression(Token*);
        bool IsCallFunction(Token*);

    private:
        AstBranch* BuildVariableDeclaration(Token*);
        AstBranch* BuildFunctionDeclaration(Token*);
        AstBranch* BuildCallFunction(Token*);
        AstBranch* BuildReturnExpression(Token*);

    private:
        Expression* BuildExpression(Tokens* token_list = nullptr);
        // BinaryOperation* ParserExpression(Tokens* tokenList, Expression* expr, uint8_t minPrecedence);
        // BinaryOperation* ParserPrimary(Tokens* tokenList, Expression* expr);
        // uint8_t GetPrecedenceValue(Token*);

};