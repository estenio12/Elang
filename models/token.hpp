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
        int start_position = 0;
        int end_position   = 0;
        std::string value  = "";
        TOKEN_DEF type    = TOKEN_DEF::IDENTIDIER;

    public:
        Token(int line           = 0,
              int start_position = 0,
              int end_position   = 0,
              std::string value  = "",
              TOKEN_DEF type    = TOKEN_DEF::IDENTIDIER):
              line(line),
              start_position(start_position),
              end_position(end_position),
              value(value),
              type(type){}
        ~Token(){}

};