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

    static const token_list ExtractArgumentListFromCallFunction(token_list list)
    {
        token_list argument_list;
        bool capture = false;

        for(auto token : list)
        {
            if(token == DELIMITERS::CLOSE_PARAM) { capture = false; continue; }
            if(token == DELIMITERS::OPEN_PARAM) { capture = true; continue; }
            if(capture && token != DELIMITERS::COMMA) argument_list.push_back(token);
        }

        return argument_list;
    }

    static const token_list ExtractFunctionFromOperationFirstInstance(token_list list)
    {
        token_list tempToken {list[0]};
        int param_open_counter = 0;

        // # Extract without argument
        if(list.size() == 4)
        {
            tempToken.push_back(list[1]);
            tempToken.push_back(list[2]);
            tempToken.push_back(list[3]);
        }
        // # Extract with argument
        else
        {
            for(auto token : list)
            {
                if(token == DELIMITERS::CLOSE_PARAM)
                {
                    tempToken.push_back(token);
                    return tempToken;
                }
                else
                {
                    tempToken.push_back(token);
                }
            }
        }

        return tempToken;
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

    static bool IsValidWorld(token target)
    {
        if(target[0] == DELIMITERS::QUOTATION_MARKS[0] &&
           target[target.length() - 1] == DELIMITERS::QUOTATION_MARKS[0])
        {
            return true;
        }

        return false;
    }

    static bool IsDigit(token target)
    {
        bool hit = false;

        for(char letter : target)
        {
            hit = false;
            
            for(char iterator : DIGIT::DIGIT)
            {
                if(letter == iterator)
                {
                    hit = true;
                }
            }

            if(!hit) return false;
        }

        return false;
    }

    static bool IsEOLCharacter(token target)
    {
        if(DELIMITERS::EOL == target) return true;
        return false;
    }

    static bool IsOpenParam(token target)
    {
        return target == DELIMITERS::OPEN_PARAM;
    }

    static bool IsCloseParam(token target)
    {
        return target == DELIMITERS::CLOSE_PARAM;
    }

    static bool IsOpenBrace(token target)
    {
        return target == DELIMITERS::OPEN_BRACE;
    }

    static bool IsCloseBrace(token target)
    {
        return target == DELIMITERS::CLOSE_BRACE;
    }
}
