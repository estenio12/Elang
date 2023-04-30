// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>

class AstNode
{
    public:
        std::string token;
        AstNode* next;

    public:
        AstNode(std::string token):token(token){next = nullptr;}
        AstNode(std::string token, AstNode* next):token(token),next(next){}
        ~AstNode(){}

    public:
        bool HasNextNode()
        { 
            if(next == nullptr) return false;
            return true; 
        }
};