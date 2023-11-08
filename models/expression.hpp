// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <queue>
#include "../definitions/token-definition.hpp"

class Tokens
{
    private:
        std::queue<Token*> list;
        std::vector<Token*> tempList;

    public:
        Tokens(){}
        ~Tokens(){}
    
    public:
        size_t GetSize(){return this->tempList.size();}
        Token* GetFirstData(){return list.front();}

        void AddToken(Token* token)
        {
            if(token != nullptr)
                tempList.push_back(token);
        }

        Token* Shift()
        {
            auto token = list.front();
            list.pop();
            return token;
        }

        std::string GetExpression()
        {
            std::string build;

            for(auto item : this->tempList)
                build += item->value;

            return build;
        }

};





