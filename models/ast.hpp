// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
#include "../models/token.hpp"
#include "../helpers/mem-tools.hpp"

using CallFunDictionary = std::vector<std::pair<std::string, class AstBranch*>>;

enum EBRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION,
    FUNCTION_DECLARATION,
    CALL_FUNCTION,
    RETURN_EXPRESSION
};

class AstNode
{
    public:
        EBRANCH_TYPE kind = EBRANCH_TYPE::UNDEFINED;

    public:
        AstNode(){}
        ~AstNode(){}

    public:
        virtual std::string GetInterface() { return ""; }
        virtual std::string GetByteCode() = 0;
};

class BinaryOperation
{
    public:
        bool IsCallFuncion = false;

    public:
        Token* token;
        BinaryOperation* left;
        BinaryOperation* right;
        class CallFunction* call_function;

    public:
        BinaryOperation(BinaryOperation* left, Token* token, BinaryOperation* right):
        token(token), left(left), right(right){}
        ~BinaryOperation(){}
};

class Expression : public AstNode
{
    public:
        bool IsLiteralOperation = true;
        bool IsConcatenation    = false;
        bool TerminateWithCloseParenthesis = false;
        BinaryOperation* operation;
        CallFunDictionary CallTable;

    public:
        Expression()
        {
            kind = EBRANCH_TYPE::EXPRESSION;
        }

        ~Expression(){}

        bool ExistCallFunctionID(std::string ID)
        {
            for(auto item : CallTable)
                if(item.first == ID) return true;
            return false;
        }

    public:
        std::string GetByteCode() override { return ""; }
};

class VariableDeclaration : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::string scopeName = "GLOBAL";
        int deep = 0;
        bool isConstant = false;
        bool isArray    = false;
        Expression* expression = nullptr;

    public:
        VariableDeclaration()
        {
            kind = EBRANCH_TYPE::VARIABLE_DECLARATION;
        }

        VariableDeclaration(VariableDeclaration* origin)
        {
            kind = EBRANCH_TYPE::VARIABLE_DECLARATION;
            operator=(origin);
        }

        ~VariableDeclaration()
        {
            delete expression;
        }

    public:
        bool IsInitialized(){ return this->expression != nullptr; }
        VariableDeclaration* operator=(const VariableDeclaration* origin)
        {
            if(this != origin)
            {
                this->name       = origin->name;
                this->type       = origin->type;
                this->scopeName  = origin->scopeName;
                this->deep       = origin->deep;
                this->isConstant = origin->isConstant;
                this->isArray    = origin->isArray;
                this->expression = origin->expression;
            }

            return this;
        }

    public:
        std::string GetByteCode() override { return ""; }
};

class CallFunction : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::vector<Expression*> ArgumetList;

    public:
        CallFunction()
        {
            this->kind = EBRANCH_TYPE::CALL_FUNCTION;
        }

        ~CallFunction()
        {
            MemTools::FreeVectorFromMemory(ArgumetList);
        }
    
    public:
        void InsertArgument(Expression* expr)
        {
            this->ArgumetList.push_back(expr);
        }
    
    public:
        std::string GetByteCode() override { return ""; }

};

class ReturnExpression : public AstNode
{
    public:
        Expression* expression;

    public:
        ReturnExpression(){this->kind = RETURN_EXPRESSION;}
        ~ReturnExpression()
        {
            delete expression;
        }

    public:
        std::string GetByteCode() override { return ""; }
};

class ParameterDeclaration
{
    public:
        std::string name;
        TYPE_TOKEN type;

    public:
        ParameterDeclaration(){}
        ~ParameterDeclaration(){}
};

class FunctionDeclaration : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::vector<ParameterDeclaration*> parameterList;

    public:
        std::vector<AstBranch*> BodyContent;

    public:
        FunctionDeclaration()
        {
            this->kind = EBRANCH_TYPE::FUNCTION_DECLARATION;
        }

        ~FunctionDeclaration()
        {
            MemTools::FreeVectorFromMemory(parameterList);
            MemTools::FreeVectorFromMemory(BodyContent);
        }

    public:
        bool IsFunctionEmpty()
        {
            return BodyContent.empty();
        }

        bool ExistsParameter(std::string name)
        {
            for(auto item : parameterList)
                if(item->name == name) return true;
            
            return false;
        }

        ParameterDeclaration* GetParameterByName(std::string name)
        {
            for(auto item : parameterList) 
                if(item->name == name) return item;

            return nullptr;
        }

    public:
        std::string GetByteCode() override { return ""; }
};

class AstBranch
{
    public:
        AstNode* entity;

    public:
        AstBranch(AstNode* entity):entity(entity){}
        ~AstBranch()
        {
            MemTools::FreeObjectFromMemory(entity);
        }
};

class Ast
{
    public:
        std::vector<AstBranch*> tree;

    public:
        Ast(){}
        ~Ast()
        {
            MemTools::FreeVectorFromMemory(tree);
        }

    public:
        void AddNode(AstBranch* branch) { this->tree.push_back(branch); }
        AstBranch* ConsumeBranch() 
        { 
            if(tree.size() > 0)
            {
                auto tmpBranch = tree[0];
                tree.erase(tree.begin(), tree.begin() + 1);
                return tmpBranch;
            }

            return nullptr;
        }
        bool HasContent() { return this->tree.size() > 0; }
};