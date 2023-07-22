// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
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
        bool isFunID = false;

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


