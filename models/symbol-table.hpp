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

class FunctionIdenfierModel
{
    public:
        std::string name;
        std::string type;
        std::vector<ParameterDeclaration*> parameterList;
        bool IsDeclared = true;

    public:
        FunctionIdenfierModel(){}
        ~FunctionIdenfierModel(){}
};

class SymbolTable
{
    private:
        std::vector<IdentifierModel*> IDTable;
        std::vector<FunctionIdenfierModel*> IDFunTable;

    public:
        SymbolTable(){}
        ~SymbolTable(){}

    private:
        int FindIndexFunTable(std::string FunName)
        {
            for(int index = 0; index < IDFunTable.size(); index++)
                if(IDFunTable[index]->name == FunName) return index;

            Output::PrintCustomizeError("Compiler internal error (in Symbol Table): ", "Function index not found");
            exit(EXIT_FAILURE);
        }

    // # Variable Declaration
    public:
        bool ExistsIdentifier(std::string name, std::string scopeName, int deep)
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

    // # Function Declaration
    public:
        bool ExistsFunctionIdentifier(std::string name)
        {
            for(auto entity : IDFunTable)
                if(entity->name == name) return true;

            return false;
        }

        FunctionIdenfierModel* GetFunctionIdentifier(std::string name)
        {
            for(auto entity : IDFunTable)
                if(entity->name == name) return entity;

            return nullptr;
        }

        void InsertFunctionIdentifier(FunctionIdenfierModel* ID) 
        { 
            if(ID != nullptr) 
            {
                if(ExistsFunctionIdentifier(ID->name) && 
                   GetFunctionIdentifier(ID->name)->IsDeclared == false)
                    this->IDFunTable[FindIndexFunTable(ID->name)] = ID;
                else
                    IDFunTable.push_back(ID);
            } 
        }
};