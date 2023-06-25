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
        int precedence;

    public:
        AstNode(Token* token):token(token){right = nullptr; left = nullptr; precedence = 0;}
        AstNode(Token* token, std::string syntax_name, int precedence, AstNode* right, AstNode* left)
        :token(token),right(right),left(left),syntax_name(syntax_name), precedence(precedence){}
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