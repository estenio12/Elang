// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <queue>
#include "./models/token.hpp"

enum BRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    FUNCTION_DECLARATION
};

class AstNode
{
    public:
        Token* token;
        AstNode* left;
        AstNode* right;

    public:
        AstNode(){}
        ~AstNode(){}
};

class AstBranch
{
    public:
        BRANCH_TYPE BranchName;
        AstNode* BranchNode;

    public:
        AstBranch(){}
        ~AstBranch(){}
};

class Ast
{
    public:
        std::queue<AstBranch*> tree;

    public:
        Ast(){}
        ~Ast(){}

    public:
        void AddNode(AstBranch* branch) { this->tree.push(branch); }
        AstBranch* GetBranch() 
        { 
            auto tmpBranch = tree.front();
            tree.pop();
            return tmpBranch;
        }

};