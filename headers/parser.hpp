// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include "../headers/lexer.hpp"

class Parser
{
    public:
        Lexer* lexer;

    public:
        Parser(Lexer* lexer;);
        ~Parser();

    public:
        void Parse();
};