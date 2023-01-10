// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <utility>

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Lexer
{
    public:
        Lexer();
        ~Lexer();

    private:
        bool IdentifyToken(std::string, Tokens_lst* );
        bool IdentifyChar(char, Tokens_lst* );

    public:
        void Tokenaze(const std::string);

    private:
        bool IsDeclarator(std::string& );
};