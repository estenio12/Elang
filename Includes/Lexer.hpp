// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Lexer
{
    private:
        Tokens_lst Tokens;

    public:
        Lexer();
        ~Lexer();

    private:
        void IdentifyToken(const std::string );


    public:
        Tokens_lst* Tokenaze(const std::string );
};