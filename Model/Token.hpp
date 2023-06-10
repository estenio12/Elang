// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>

class Token
{
    public:
        std::string value;
        std::string type;
        long line    = 0;
        int startPos = 0;
        int endPos   = 0;

    public:
        Token(std::string value,
              std::string type,
              long line    = 0,
              int startPos = 0,
              int endPos   = 0)
              :
              value(value),
              type(type),
              line(line),
              startPos(startPos),
              endPos(endPos)
              {}
        ~Token(){}

};


