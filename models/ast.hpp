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

enum BRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION
};

class AstNode
{
    public:
        BRANCH_TYPE kind = BRANCH_TYPE::UNDEFINED;

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
        bool IsLiteralOperation = false;
        BinaryOperation* operation;

    public:
        Expression()
        {
            kind = BRANCH_TYPE::EXPRESSION;
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
            kind = BRANCH_TYPE::VARIABLE_DECLARATION;
        }

        ~VariableDeclaration(){}
};

class AstBranch
{
    public:
        BRANCH_TYPE TYPE = BRANCH_TYPE::UNDEFINED;

    public:
        class VariableDeclaration* branch_variable_declaration;

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
        ~Ast(){}

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