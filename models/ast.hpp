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
    VARIABLE_DECLARATION
};

class AstNode
{
    public:
        BRANCH_TYPE kind = BRANCH_TYPE::UNDEFINED;

    public:
        AstNode(){}
        ~AstNode(){}
};

class VariableDeclaraion : public AstNode
{
    kind = BRANCH_TYPE::VARIABLE_DECLARATION;
    std::string name;
    std::string type;
    std::string scopeName = "GLOBAL";
    int deep = 0;
    bool isConstant = false;
};

class Ast
{
    public:
        std::vector<AstNode*> tree;

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