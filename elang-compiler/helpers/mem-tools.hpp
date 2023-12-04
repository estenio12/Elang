// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "../models/ast.hpp"

namespace MemTools
{
    /// @brief Free vector pointers from memory
    /// @tparam T 
    /// @param vector 
    template<class T> void FreeVectorFromMemory(T vector)
    {
        for(auto item : vector) 
            if(item != nullptr) delete item;
        vector.clear();
    }

    /// @brief Delete an object from memory
    /// @tparam T 
    /// @param entity 
    template<class T> void FreeObjectFromMemory(T* entity)
    {
        if(entity != nullptr) delete entity;
    }
}