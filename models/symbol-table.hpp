// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
#include "../models/ast.hpp"

class SymbolTable
{
    private:
        std::vector<VariableDeclaration*> IDTable;

    public:
        SymbolTable(){}
        ~SymbolTable(){}

    public:
        bool Exists(std::string name, std::string scopeName, int deep)
        {
            for(auto entity : IDTable)
            {
                if(entity->name == name && 
                  (entity->scopeName == scopeName || entity->scopeName == "GLOBAL") &&
                   entity->deep <= deep)
                {
                    return true;
                }
            }

            return false;
        }

};