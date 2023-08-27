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
#include <iostream>
#include "../Model/Token.hpp"

class ScopeModel
{
    public:
        int id;
        std::string name;
        std::string type;
        Token* token;
        int deep;

    public:
        ScopeModel(int id,
                   std::string name,
                   std::string type,
                   Token* token,
                   int deep):
                   id(id),
                   name(name),
                   type(type),
                   token(token),
                   deep(deep)
                   {}
        ~ScopeModel(){}
};


class ScopeTable
{
    private:
        int IDCounter = 0;
        std::vector<ScopeModel*> table;

    public:
        ScopeTable(){}    
        ~ScopeTable(){}

    public:
        void InsertRow(std::string name,
                       std::string type,
                       Token* token,
                       int deep)
        {
            auto row = new ScopeModel(++IDCounter, name, type, token, deep); 
            this->table.push_back(row);
        }

        ScopeModel* GetCurrentScope()
        {
            if(this->table.empty()) return nullptr;
            return this->table.back();
        }

        int GetCurrentID()
        {
            if(this->table.empty()) return 0;
            return this->table.back()->id;
        }

        int CloseScope()
        {
            if(!this->table.empty())
            {
                int id = this->GetCurrentScope()->id;
                this->table.pop_back();

                return id;
            }

            return 0;
        }

        void PrintDebug()
        {
            for(auto t : this->table)
            {
                std::cout << "Debug: " << t->name << "\n";
            }
        }
};






