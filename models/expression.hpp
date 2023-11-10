// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "../definitions/token-definition.hpp"

class Tokens
{
    private:
        std::vector<Token*> list;

    public:
        Tokens(){}
        ~Tokens(){}
    
    public:
        size_t GetSize(){return this->list.size();}
        Token* GetFirstData(){return list.front();}

        void AddToken(Token* token)
        {
            if(token != nullptr)
                list.push_back(token);
        }

        Token* Shift()
        {
            auto token = list.front();
            list.erase(list.begin(), list.begin() + 1);

            if(list.size() == 0) return nullptr;
            return token;
        }

        std::string GetExpression()
        {
            std::string build;

            for(auto item : this->list)
                build += item->value;

            return build;
        }
};





