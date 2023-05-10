// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <fstream>
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Tools.hpp"
#include "../Include/Output.hpp"

class Lexer
{
    private:
        std::ifstream fileHandler;
        token_list currentTokenList;

    private:
        int cursorTokenList = 0;
        int lineCounter     = 0;
        bool FileIsOpen = true;

    public:
        bool FileIsEnd  = false;

    public:
        Lexer(std::string sourceCodePath);
        ~Lexer();

    public:
        token GetNextToken();
        int GetLineCounter(){ return this->lineCounter; }

    private:
        void CheckTokenList();
        token_list Tokenize(std::string );
        std::string GetNextLineFromFile(); 

    private:
        bool IsNotAlphaNumeric(char ); 
        token ConvertCharacterToToken(char );
        std::string SanitizeLine(std::string );
};