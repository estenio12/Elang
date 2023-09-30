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

enum EBRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION,
    FUNCTION_DECLARATION
};

class AstNode
{
    public:
        EBRANCH_TYPE kind = EBRANCH_TYPE::UNDEFINED;

    public:
        AstNode(){}
        ~AstNode(){}
};

class BinaryOperation
{
    public:
        Token* token;
        BinaryOperation* left;
        BinaryOperation* right;

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
        BinaryOperation* operation;

    public:
        Expression()
        {
            kind = EBRANCH_TYPE::EXPRESSION;
        }

        ~Expression(){}
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
        std::vector<VariableDeclaration*> listBodyLocalVariableDeclaration;

    public:
        FunctionDeclaration(){}
        ~FunctionDeclaration(){}

    public:
        bool IsFunctionEmpty()
        {
            return listBodyLocalVariableDeclaration.size() <= 0;
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

};

class AstBranch
{
    public:
        EBRANCH_TYPE TYPE = EBRANCH_TYPE::UNDEFINED;

    public:
        class VariableDeclaration* branch_variable_declaration = nullptr;
        class FunctionDeclaration* branch_function_declaration = nullptr;

    public:
        AstBranch(){}
        ~AstBranch(){}
};

class Ast
{
    public:
        std::vector<AstBranch*> tree;

    public:
        Ast(){}
        ~Ast()
        {
            tree.clear();
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
};