// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
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
        std::vector<AstBranch*> tree;

    public:
        Ast(){}
        ~Ast(){}

    public:
        void AddNode(AstBranch* branch) { this->tree.push(branch); }
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