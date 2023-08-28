// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) All Right reserved
// ## @License: Apache 2.0
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
        bool macroFlag = false;

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
        void BuildToken(std::string value, 
                        std::string type, 
                        int startPos, 
                        int endPos);
        std::string ConvertToString(char );
        void ThrowError(std::string, int);
        std::string Sanitaze(std::string );

    private:
        bool IsDigit(char );
        bool IsAlpha(char );
        bool IsDelimiter(char );
        bool IsArithmatic(char );
        bool IsComparison(char );
        bool IsLogical(char );
        bool IsAttribution(char );

    private:
        Token* BindToken(std::string );
        Token* BindType(std::string );
        Token* BindKeyword(std::string );
        Token* BindBoolean(std::string );
        Token* BindDelimiters(std::string );
};