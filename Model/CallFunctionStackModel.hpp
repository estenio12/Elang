// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <vector>

class CallStackModel
{
    public:
        std::string ID;
        std::string type;
        int param_id;
        int parem_counter;
        

    public: 
        CallStackModel(){}
        CallStackModel(std::string ID,
                       std::string type,
                       int param_id,
                       int parem_counter):
                       ID(ID),
                       type(type),
                       param_id(param_id),
                       parem_counter(parem_counter)
                       {}
        ~CallStackModel(){}
};

class CallStack
{
    private:
        std::vector<CallStackModel*> stack;

    public:
        std::string ExpectedTypeHistory;

    public:
        CallStack(){}
        ~CallStack(){}

    public:
        void Insert(CallStackModel* item)
        {
            this->stack.push_back(item);
        }

        CallStackModel* GetCurrentItem()
        {
            if(this->stack.size() > 0) return this->stack.back();
            return nullptr;
        }

        /// @return 'true' if the stack is empty 
        bool PopBack()
        {
            this->stack.pop_back();
            return this->IsEmpty();
        }

        bool IsEmpty()
        {
            return this->stack.size() <= 0;
        }

        bool RemoveParemCounter()
        {
            this->stack.back()->parem_counter--;
            if(this->stack.back()->parem_counter <= 0) return this->PopBack();
            return false;
        }
};