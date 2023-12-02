// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <cstdint>
#include <vector>

class BlockStmtPolicy
{
    private:
        std::vector<uint8_t> policy_list;

    public:
        BlockStmtPolicy(){}
        ~BlockStmtPolicy(){}

    public:
        bool HasPolicy(uint8_t policy)
        {
            for(auto item : policy_list)
            {
                if(item == policy)
                    return true;
            }

            return false;
        }

        void AddPolicy(uint8_t policy)
        {
            if(!this->HasPolicy(policy))
                this->policy_list.push_back(policy);
        }

        void ClearPolicy()
        {
            this->policy_list.clear();
        }
};
