// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

namespace MemTools
{
    /// @brief Free vector pointers from memory
    /// @tparam T 
    /// @param vector 
    template<class T> void FreeVectorFromMemory(T vector)
    {
        for(auto item : vector) delete item;
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