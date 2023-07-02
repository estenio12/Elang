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

#include "../Model/FunctionIDModel.hpp"
#include "../Helpers/Definition.hpp"

class IDFunctionDeclarationStorage
{
    private:
        std::vector<FunctionIDModel*> IDTable;

    private:
        int globalIdCounter = 0;

    public:
        IDFunctionDeclarationStorage();
        ~IDFunctionDeclarationStorage();

    public:
        void InsertFunctionID(FunctionIDModel* row);
        bool ExistIdentifier(std::string name);
        FunctionIDModel* FindObjectIdentifier(std::string name, std::string type);
        FunctionIDModel* CreateRow(std::string name, std::string type);
};