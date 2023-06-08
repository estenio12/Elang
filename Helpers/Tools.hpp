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

        std::string CropString(std::string source)
        {
            return source.substr(1, source.length() - 2);
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

class Checker
{
    public:
        Checker(){}
        ~Checker(){}

    public:
        bool IsValidLine(std::string line)
    {
        for(char letter : line)
        {
            if(letter != DELIMITERS::WHITESPACE[0] && 
               letter != DELIMITERS::BACKSPACE[0]  && 
               letter != DELIMITERS::TABULATION[0] && 
               letter != DELIMITERS::NEWLINE[0] )
            {
                return true;
            }
        }

        return false;
    }

        bool IsValidType(token target)
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

        bool IsValidIdentifier(token target)
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

        bool IsValidWorld(token target)
    {
        if(target[0] == DELIMITERS::QUOTATION_MARKS[0] &&
           target[target.length() - 1] == DELIMITERS::QUOTATION_MARKS[0])
        {
            return true;
        }

        return false;
    }

        bool IsDigit(token target)
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

        bool IsEOLCharacter(token target)
    {
        if(DELIMITERS::EOL == target) return true;
        return false;
    }

        bool IsOpenParam(token target)
    {
        return target == DELIMITERS::OPEN_PARAM;
    }

        bool IsCloseParam(token target)
    {
        return target == DELIMITERS::CLOSE_PARAM;
    }

        bool IsOpenBrace(token target)
    {
        return target == DELIMITERS::OPEN_BRACE;
    }

        bool IsCloseBrace(token target)
    {
        return target == DELIMITERS::CLOSE_BRACE;
    }
};
