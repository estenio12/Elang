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
#include "../definitions/block-stmt-policy.hpp"

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
        void ExpectThisToken(Token* token, std::string expected, std::string message);
        void ThrowError(Token*, std::string message);
        void ThrowErrorDataType(Token*, std::string type_token, std::vector<std::string> expected_type);
        void ThrowInternalError(std::string message);
        void PushToAst(AstBranch* node);
        void InsertIdentifierIntoSymbolTable(VariableDeclaration*);
        Token* GetNextToken(std::string msg);
        std::string GenerateCallFunctionHash();
        std::vector<Tokens*> GetNewInstanceOfArgumentList(int ArgumentSize);
        TYPE_IDENTIFIER GetTypeIdentifier(Token* token, const std::vector<std::string> expected_type);
        bool IsValidDataType(Token* token, std::vector<std::string> expected_type);
        std::string ConvertTypeTokenToType(TYPE_TOKEN type);
        std::vector<std::string> CreateExpectedType(std::string type);

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
        bool IsAssignment(Token*);
        bool IsWhileDeclaration(Token*);

    private:
        AstBranch* BuildVariableDeclaration(Token*);
        AstBranch* BuildFunctionDeclaration(Token*);
        AstBranch* BuildCallFunction(Token*, Tokens* list = nullptr);
        AstBranch* BuildReturnExpression(Token*, std::string expected_type);
        AstBranch* BuildAssignment(Token*);
        AstBranch* BuildBreakStatement(Token*);
        AstBranch* BuildWhileDeclaration(BlockStmtPolicy*, Token*);

    private:
        BlockStatement* BuildBlockStatement(BlockStmtPolicy*, std::string);
        Expression* BuildExpression(const std::vector<std::string> expected_type, Tokens* token_list = nullptr);

};