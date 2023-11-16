// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include "../definitions/token-definition.hpp"

class Tokens
{
    private:
        std::vector<Token*> list;
        std::string expected_type;

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
            if(list.size() == 0) return nullptr;
            
            auto token = list.front();
            list.erase(list.begin(), list.begin() + 1);

            return token;
        }

        std::string GetExpression()
        {
            std::string build;

            for(auto item : this->list)
                build += item->value;

            return build;
        }

        std::string GetExpectedType()
        {
            return this->expected_type;
        }

        void SetExpectedType(std::string expectedType)
        {
            this->expected_type = expected_type;
        }
};





