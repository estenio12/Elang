// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <vector>

using FunctionParameterList = std::vector<std::pair<std::string, std::string>>;

class FunctionIDModel
{
    public:
        std::string name;
        std::string type;
        /// @param 1 type
        /// @param 2 name
        FunctionParameterList paramList;

    public:
        FunctionIDModel(std::string name, std::string type):name(name), type(type){}
        ~FunctionIDModel(){}
};