// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Model/IDModel.hpp"
#include "../Helpers/Definition.hpp"

class IDStorage
{
    private:
        std::vector<IDModel*> IDTable;

    private:
        int globalIdCounter = 0;

    public:
        IDStorage();
        ~IDStorage();

    public:
        void InsertID(IDModel* row);
        bool ExistIdentifier(std::string name, std::string scopeName, int deep);
        IDModel* FindObjectIdentifier(std::string name);
        IDModel* CreateRow(std::string name, std::string value, std::string type, std::string typeValue, 
                           std::string scopeName, int IDScopeTable, int deep, bool isConstant);
        void RemoveID(int ID);
        void PrintDebug();
};