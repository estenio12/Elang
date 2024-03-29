///////////////////////////
// @author: Estenio Garcia
// @license: Apache 2.0
// @copyright: all
///////////////////////////

#pragma once

#include <string>
#include "../definitions/token-definition.hpp"

class Token
{
    public:
        int line          = 0;
        int startpos      = 0;
        int endpos        = 0;
        std::string value = "";
        TYPE_TOKEN type   = TYPE_TOKEN::T_IDENTIDIER;

    public:
        bool isCallFunction = false;

    public:
        Token(int line           = 0,
              int start_position = 0,
              int end_position   = 0,
              std::string value  = "",
              TYPE_TOKEN type    = TYPE_TOKEN::T_IDENTIDIER):
              line(line),
              startpos(start_position),
              endpos(end_position),
              value(value),
              type(type){}
        ~Token(){}

        Token* GetCopy()
        {
            auto token      =  new Token();
            token->endpos   = this->endpos;
            token->startpos = this->startpos;
            token->line     = this->line;
            token->value    = this->value;
            token->type     = this->type;

            return token;
        }

};
