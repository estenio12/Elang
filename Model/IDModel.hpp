// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>

class IDModel
{
    public:
        int ID = 0;
        std::string name;
        std::string value;
        std::string type;
        std::string scopeName;
        int deep = 0;

    public:
        IDModel(){}
        IDModel(std::string name,
                std::string value,
                std::string type,
                std::string scopeName,
                int deep = 0):
            name(name),
            value(value),
            type(type),
            scopeName(scopeName),
            deep(deep){}
};