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

namespace Tools
{
    static const bool Contains(std::string source, char target)
    {
        for(char letter : source) if(letter == target) return true;
        return false;
    }

    static const std::string CropString(std::string source)
    {
        return source.substr(1, source.length() - 2);
    } 

    static const std::string TrimString(std::string source)
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
}

namespace Checker
{
    static bool IsValidLine(std::string line)
    {
        for(char letter : line)
        {
            if(letter != DELIMITERS::WHITESPACE[0] && 
               letter != DELIMITERS::RETURNING[0]  && 
               letter != DELIMITERS::TABULATION[0] && 
               letter != DELIMITERS::NEWLINE[0] )
            {
                return true;
            }
        }

        return false;
    }

    static bool IsValidType(token target)
    {
        for(auto token : TYPE::TYPE)
        {
            if(token == target)
            {
                return true;
            }
        }

        return false;
    }

    static bool IsValidIdentifier(token target)
    {
        bool hit = false;

        for(char letter : target)
        {
            hit = false;

            for(auto Aletter : ALPHA::ALPHANUMERIC)
            {
                if(letter == Aletter)
                {
                    hit = true;
                }
            }

            if(!hit) return false;
        }

        return true;
    }

    static bool IsEOLCharacter(token target)
    {
        if(DELIMITERS::EOL == target) return true;
        return false;
    }

}
