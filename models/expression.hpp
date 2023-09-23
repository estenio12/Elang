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

    public:
        Tokens(){}
        ~Tokens(){}
    
    public:
        size_t GetSize(){return this->list.size();}
        Token* GetFirstData(){return list.front();}

        void AddToken(Token* token)
        {
            if(token != nullptr)
                list.push(token);
        }

        Token* Shift()
        {
            auto token = list.front();
            list.pop();
            return token;
        }

};





