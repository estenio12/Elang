// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <queue>
#include <fstream>
#include <filesystem>
#include "../definitions/token-definition.hpp"
#include "../models/token.hpp"
#include "./output.hpp"

class Lexer
{
    private:
        enum JOB_STATE
        {
            UNDEFINED,
            BUILD_DIGIT,
            BUILD_ALPHA_DIGIT
        };

    private:
        std::queue<Token*> tokenPool;
        std::ifstream fileHanler;
        std::string sourcePath;
        bool endTokenize = false;

    private:
        const int MIN_POOL_SIZE = 5;  

    public:
        int lineCounter = 0;
        
    public:
        Lexer(std::string sourcePath);
        ~Lexer();

    public:
        Token* GetNextToken();
        
    private:
        void LoadMoreToken();
        void LoadFileHandler();
        bool IsValidPath();
        std::string Sanitaze(std::string line);

    private:
        void Tokenize(std::string line);
        void CheckOutOfMemoryBuildToken(Token*);

    private:
        Token* BindToken(std::string chunk);

    private:
        bool IsDigit(char letter);
        bool IsDigitFloat(std::string buffer);
        bool IsAlphaNumetic(char letter);

    private:
        void BuildLiteralFloatToken(std::string value, int startpos, int endpos);
        void BuildLiteralIntToken(std::string value, int startpos, int endpos);
};