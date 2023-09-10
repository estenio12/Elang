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
#include "../headers/output.hpp"

class DebugToken
{
    public:
        DebugToken(){}
        ~DebugToken(){}

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

    public:
        void printToken(Token* token)
        {
            if(token != nullptr)
            {
                std::string buffer = token->value + " | " + GetTypeText(token->type) + " | " + std::to_string(token->startpos) + " | " + std::to_string(token->endpos);
                Output::PrintDebug(buffer);
            }
        }
};