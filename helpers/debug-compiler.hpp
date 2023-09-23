// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "../definitions/token-definition.hpp"
#include "../models/token.hpp"
#include "../models/ast.hpp"
#include "../headers/output.hpp"

class DebugCompiler
{
    public:
        DebugCompiler(){}
        ~DebugCompiler(){}

    private:
        std::string GetTypeText(TYPE_TOKEN type)
        {
            switch (type)
            {
                case TYPE_TOKEN::T_KEYWORD:        return "KEYWORD";
                case TYPE_TOKEN::T_TYPE:           return "TYPE";
                case TYPE_TOKEN::T_IDENTIDIER:     return "IDENTIFIER";
                case TYPE_TOKEN::T_DELIMITER:      return "DELIMITER";
                case TYPE_TOKEN::T_ARITHMETIC:     return "ARITHMETIC";
                case TYPE_TOKEN::T_PREFIX:         return "PREFIX";
                case TYPE_TOKEN::T_POSTFIX:        return "POSTFIX";
                case TYPE_TOKEN::T_LOGICAL:        return "LOGICAL";
                case TYPE_TOKEN::T_FLOAT_LITERAL:  return "FLOAT_LITERAL";
                case TYPE_TOKEN::T_INT_LITERAL:    return "INT_LITERAL";
                case TYPE_TOKEN::T_CHAR_LITERAL:   return "CHAR_LITERAL";
                case TYPE_TOKEN::T_BOOL_LITERAL:   return "BOOL_LITERAL";
                case TYPE_TOKEN::T_STRING_LITERAL: return "STRING_LITERAL";
                default: return "Not found";
            }
        }

    private:
        void printVariableDeclaration(VariableDeclaration* node)
        {
            std::cout << "DEBUG BRANCH: " << "VARIABLE DECLARATION" << "\n";
            std::cout << "name........: " << node->name << "\n";
            std::cout << "type........: " << node->type << "\n";
            std::cout << "scope.......: " << node->scopeName << "\n";
            std::cout << "deep........: " << node->deep << "\n";
            std::cout << "is constant.: " << (node->isConstant ? "true" : "false") << "\n";
            std::cout << "is array....: " << (node->isArray ? "true" : "false") << "\n";
        }

    public:
        void PrintToken(Token* token)
        {
            if(token != nullptr)
            {
                std::string buffer = token->value + " | " + GetTypeText(token->type) + " | " + std::to_string(token->startpos) + " | " + std::to_string(token->endpos);
                Output::PrintDebug(buffer);
            }
        }
        
        void PrintAstBranch(AstBranch* node)
        {
            if(node->TYPE == BRANCH_TYPE::VARIABLE_DECLARATION) printVariableDeclaration(node->branch_variable_declaration);
        }
};