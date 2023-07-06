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
#include "../Include/IDFunctionDeclarationStorage.hpp"
#include "../Model/Ast.hpp"
#include "../Model/FunctionIDModel.hpp"
#include "../Include/CodeGenerator.hpp"

class Parser
{
    private:
        AST ast;
        Lexer* lexer;
        Tools* tool;
        IDDeclarationStorage* IDTable;
        IDFunctionDeclarationStorage* IDFunTable;
        CodeGenerator* codegen;

    private:
        AstNode* buildingNode;
        Token* history;
        int currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
        int observer      = BRANCH_IDENTIFIER::UNDEFINED;
        std::string expectedType = EXPECTED_TYPE::TUNDEFINED;
        std::string currentScope = STANDARD_SCOPE_NAME::GLOBALSCOPE;
        int currentDeep = 0;
        bool isConstant = false;

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
        AstNode* FindLastNode(AstNode*, uint8_t );
        Token* ConsumeNextTokenFromBuffer();
        void AddParemCounter();
        void RemoveParemCounter();
        void AddDeepCounter();
        void RemoveDeepCounter();
        std::string GetExpectedType(Token* );
        void CommitEntity(std::string, AstNode* );

    // # Main Entities
    private:
        int VariableDeclarationDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
        AstNode* VariableDeclarationBuildingNode = nullptr;
        AstNode* VariableDeclaration(Token* );
        void InsertVariableDeclarationNode(Token*, int );
        void VariableDeclarationCommit();

    private:
        AstNode* FunctionDeclarationBuildingNode;
        std::string currentFunctionType = EXPECTED_TYPE::TVOID;
        int FunctionDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
        AstNode* FunctionDeclaration(Token* );
        void FunctionDeclarationReset();
        void InsertFunctionDeclarationNode(Token*, int );

    // # Functions Assistants
    private:
        int StatementState = BRANCH_IDENTIFIER::UNDEFINED;
        AstNode* StatementBuildingNode;
        AstNode* Statement(Token* );
        void InsertStatementNode(Token*, int );
        void ResetStatementBuildingNode();

    private:
        int ExpressionParemCounter = 0;
        std::string ExpressionExpectedType = EXPECTED_TYPE::TUNDEFINED;
        AstNode* ExpressionBuildingNode;
        AstNode* Expression(Token*, std::string);
        bool ExpressionCheckOpenParam(Token* );
        bool ExpressionCheckType(Token* );
        bool ExpressionCheckIdentifier(Token*);
        void ResetExpressionBuildingNode();
        void InsertExpressionNode(Token*, int );

    private:
        std::string currentParameterType = EXPECTED_TYPE::TVOID;
        AstNode* ParameterListBuildingNode;
        FunctionParameterList parameterList;
        AstNode* BuildParameterList(Token* );
        void InsertParameterListNode(Token*, int);
        void BuildParameterListCommit();
        void ResetParameterListBuildingNode();
        void ResetBuildParameterListStates();
};