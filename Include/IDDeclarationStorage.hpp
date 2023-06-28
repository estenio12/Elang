// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Model/IDModel.hpp"

class IDDeclarationStorage
{
    private:
        std::vector<IDModel*> IDTable;

    private:
        int globalIdCounter = 0;

    public:
        IDDeclarationStorage();
        ~IDDeclarationStorage();

    public:
        void InsertID(IDModel* row);
        bool ExistIdentifier(std::string name);
        IDModel* FindObjectIdentifier(std::string name);
        IDModel* CreateRow(std::string name, std::string value, std::string type, std::string typeValue, 
                           std::string scopeName, int deep, bool isConstant);
};