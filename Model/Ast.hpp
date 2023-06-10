// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
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

    public:
        AstNode(Token* token):token(token){right = nullptr; left = nullptr;}
        AstNode(Token* token, std::string syntax_name, AstNode* right, AstNode* left)
        :token(token),right(right),left(left),syntax_name(syntax_name){}
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
};