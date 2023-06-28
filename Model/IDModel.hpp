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
        std::string typeValue;
        std::string scopeName;
        int deep = 0;
        bool isConstant = false;

    public:
        IDModel(){}
        IDModel(std::string name,
                std::string value,
                std::string type,
                std::string typeValue,
                std::string scopeName,
                int deep = 0,
                bool isConstant = false):
            name(name),
            value(value),
            typeValue(typeValue),
            type(type),
            scopeName(scopeName),
            deep(deep),
            isConstant(isConstant){}
};