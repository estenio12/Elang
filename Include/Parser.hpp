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
#include <optional>
#include "../Helpers/Tools.hpp"
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Include/Output.hpp"
#include "../Include/LexicalAnalyser.hpp"
#include "../Include/IDDeclarationStorage.hpp"
#include "../Include/IDFunctionDeclarationStorage.hpp"
#include "../Model/Ast.hpp"
#include "../Model/FunctionIDModel.hpp"
#include "../Model/CallFunctionStackModel.hpp"
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
        CallStack* expressionFunctionStack;

    private:
        AstNode* buildingNode;
        Token* history;
        int currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
        int observer      = BRANCH_IDENTIFIER::UNDEFINED;
        std::string expectedType = EXPECTED_TYPE::TUNDEFINED;
        std::string currentScope = STANDARD_SCOPE_NAME::GLOBALSCOPE;
        int currentDeep = 0;
        bool isConstant = false;
        const std::string EMPTY = "-1";

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
        std::string GetExpectedTypeByValue(Token* );
        std::string GetExpectedTypeByType(Token* );
        void CommitEntity(std::string, AstNode* );
        int IdentifyTypeID(std::string name);

    // # Main Entities
    private:
        int VariableDeclarationDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
        AstNode* VariableDeclarationBuildingNode = nullptr;
        AstNode* VariableDeclaration(Token* );
        void InsertVariableDeclarationNode(Token*, int );
        void VariableDeclarationCommit();
        void ResetVariableDeclarationBuildingNode();

    private:
        AstNode* FunctionDeclarationBuildingNode;
        std::string currentFunctionType = EXPECTED_TYPE::TVOID;
        int FunctionDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
        AstNode* FunctionDeclaration(Token* );
        void FunctionDeclarationReset();
        void InsertFunctionDeclarationNode(Token*, int );

    // # Assistants Methods
    private:
        int StatementState = BRANCH_IDENTIFIER::UNDEFINED;
        const std::vector<std::pair<std::string, AstNode*>> ReturnEmptyStatementList;
        std::vector<std::pair<std::string, AstNode*>> StatementList;
        std::vector<std::pair<std::string, AstNode*>> Statement(Token* );
        void InsertStatementNode(Token*, int );
        void ResetStatementList();
        int StatementTypeIdentifier(Token* );

    private:
        int ExpressionParemCounter = 0;
        int ExpressionCommaCounter = 0;
        bool ExpressionDoOnce = false;
        std::string ExpressionExpectedType = EXPECTED_TYPE::TUNDEFINED;
        AstNode* ExpressionBuildingNode;
        AstNode* Expression(Token*, std::string expectedType);
        bool ExpressionCheckOpenParam(Token* );
        bool ExpressionCheckCloseParam(Token* );
        bool ExpressionCheckType(Token* );
        bool ExpressionCheckIdentifier(Token*);
        void ResetExpressionBuildingNode();
        void InsertExpressionNode(Token*, int );
        void IncrementExpressionCommaCounter(int );
        void DecrementExpressionCommaCounter();
        CallStackModel* BuildCallStackModel(std::string ID, std::string type, int param_id, int parem_counter);

    private:
        std::string currentParameterType = EXPECTED_TYPE::TVOID;
        AstNode* ParameterListBuildingNode;
        FunctionParameterList parameterList;
        AstNode* BuildParameterList(Token* );
        void InsertParameterListNode(Token*, int);
        void BuildParameterListCommit();
        void ResetParameterListBuildingNode();
        void ResetBuildParameterListStates();

    private:
        int AssignmentState = BRANCH_IDENTIFIER::UNDEFINED;
        std::string AssignmentExpectedType = EXPECTED_TYPE::TUNDEFINED;
        AstNode* AssignmentBuildingNode;
        AstNode* Assignment(Token* );
        void InsertAssignmentBuildNode(Token*, int );
        void ResetAssignmentBuildNode();

    private:
        int ArgumentIndex = 0;
        int CallFunctionState = BRANCH_IDENTIFIER::UNDEFINED;
        std::string CurrentArgumentExpectedType = EXPECTED_TYPE::TUNDEFINED;
        std::string CurrentArgumentListFunctionName;
        AstNode* CallFunctionBuildingNode;
        AstNode* CallFunction(Token* );
        void InsertCallFunctionBuildNode(Token*, int );
        void ResetCallFunctionBuildNode();
        void IncrementArgumentIndex();
        std::string GetNextArgumentType();

    private:
        int ConditionState = BRANCH_IDENTIFIER::UNDEFINED;
        int ConditionParamCounter = 0;
        int ConditionStmtCounter = 0;
        std::string ConditionTypeExpression = "";
        AstNode* ConditionBuildNode;
        AstNode* ConditionDeclaration(Token* );
        void InsertConditionBuildNode(Token*, int);
        void ResetConditionBuildNode();
        void ConditionOpenParam();
        void ConditionCloseParam();
        void AddConditionStmtCounter();
        void RemoveConditionStmtCounter();

    private:
        AstNode* CloseStatment(Token* );
};