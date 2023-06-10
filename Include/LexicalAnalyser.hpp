// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <fstream>
#include <vector>
#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Tools.hpp"
#include "../Include/Output.hpp"

class Lexer
{
    private:
        Tools* tools;

    private:
        std::ifstream fileHandler;
        std::vector<Token*> tokenList;

    private:
        int lineCounter = 0;

    public:
        Lexer(std::string sourceCodePath);
        ~Lexer();

    public:
        Token* GetNextToken();
        int GetLineCounter(){ return this->lineCounter; }

    private:
        Token* GetToken();
        void LoadLineFromFile();
        void Tokenize(std::string line);
        bool IsSkipCharacter(char* );
        void BuildToken(std::string value, 
                        std::string type, 
                        int startPos, 
                        int endPos);
        Token* BindToken(std::string );

    private:
        bool IsDigit(char* );
        bool IsAlpha(char* );

    private:
        Token* IsType(std::string );
        Token* IsKeyword(std::string );
        Token* IsBoolean(std::string );
};