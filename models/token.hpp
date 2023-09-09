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
        int line           = 0;
        int startpos = 0;
        int endpos   = 0;
        std::string value  = "";
        TOKEN_DEF type    = TOKEN_DEF::T_IDENTIDIER;

    public:
        Token(int line           = 0,
              int start_position = 0,
              int end_position   = 0,
              std::string value  = "",
              TOKEN_DEF type    = TOKEN_DEF::T_IDENTIDIER):
              line(line),
              startpos(start_position),
              endpos(end_position),
              value(value),
              type(type){}
        ~Token(){}

};