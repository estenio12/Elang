// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Tools.hpp"

class Lexer
{
    public:
        Lexer();
        ~Lexer();

    public:
        token_list Tokenize(std::string );

    private:
        bool IsNotAlphaNumeric(char ); 
        token ConvertCharacterToToken(char );
};