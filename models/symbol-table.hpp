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

class IdentifierModel
{
    public:
        std::string name; 
        std::string type; 
        std::string scopeName; 
        int deep;

    public:
        IdentifierModel(std::string name, std::string type, std::string scopeName, int deep):
        name(name), type(type), scopeName(scopeName), deep(deep){}
        ~IdentifierModel(){}
};

class SymbolTable
{
    private:
        std::vector<IdentifierModel*> IDTable;

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

        void InsertIdentifier(IdentifierModel* ID) { if(ID != nullptr) IDTable.push_back(ID); }

        IdentifierModel* GetIdentifier(std::string name, std::string scopeName, int deep)
        {
            for(auto entity : IDTable)
            {
                if(entity->name == name && 
                  (entity->scopeName == scopeName || entity->scopeName == "GLOBAL") &&
                   entity->deep <= deep)
                {
                    return entity;
                }
            }

            return nullptr;
        }
};