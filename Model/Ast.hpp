// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include "../Model/Token.hpp"

class AstNode
{
    public:
        std::string syntax_name;
        Token* token;
        AstNode* right;
        AstNode* left;
        AstNode* parent;

    public:
        AstNode(Token* token):token(token){right = nullptr; left = nullptr; parent = nullptr; }
        AstNode(Token* token, std::string syntax_name, int precedence, AstNode* right, AstNode* left, AstNode* parent)
        :token(token),right(right),left(left),syntax_name(syntax_name), parent(parent){}
        ~AstNode(){}

    public:
        bool HasRightNode()
        { 
            if(right == nullptr) return false;
            return true; 
        }

        bool HasLeftNode()
        { 
            if(left == nullptr) return false;
            return true; 
        }

        bool HasAnyNode()
        {
            return this->HasLeftNode() || this->HasRightNode();
        }
};