// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Definition.hpp"

class Tools
{
    public:
        Tools(){}
        ~Tools(){}

    public:
        bool Contains(std::string source, char target)
        {
            for(char letter : source) if(letter == target) return true;
            return false;
        }

        std::string TrimString(std::string source)
        {
            std::string nstring = "";

            for(char letter : source)
            {
                if(letter != ' ')
                {
                    nstring.push_back(letter);
                }
            }

            return nstring;
        }

};
