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

class IDFunctionStorage
{
    private:
        std::vector<FunctionIDModel*> IDTable;

    private:
        int globalIdCounter = 0;

    public:
        IDFunctionStorage();
        ~IDFunctionStorage();

    public:
        void InsertFunctionID(FunctionIDModel* row);
        bool ExistIdentifier(std::string name);
        FunctionIDModel* FindObjectIdentifier(std::string name, std::string type);
        FunctionIDModel* FindObjectIdentifier(std::string name);
        FunctionIDModel* CreateRow(std::string name, std::string type);
};