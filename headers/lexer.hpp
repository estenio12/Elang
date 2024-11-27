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
            BUILD_ALPHA_DIGIT,
            BUILD_STRING_LITERAL
        };

    private:
        std::queue<Token*> tokenPool;
        std::ifstream fileHandler;
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
        std::string Sanitaze(std::string line);

    private:
        void Tokenize(std::string line);
        void CheckOutOfMemoryBuildToken(Token*);

    private:
        void BindToken(std::string value, int startpos, int endpos);

    private:
        bool IsDigit(char letter);
        bool IsDigitFloat(std::string buffer);
        bool IsAlpha(char letter);
        bool IsAlphaNumetic(char letter);
        bool IsDelimiter(std::string value);
        bool IsSelfIncrementation(std::string value);
        int IsArithmetic(std::string value);
        int IsLogical(std::string value);
        TYPE_TOKEN GetTypeSelfIncrementation();

    private:
        void BuildToken(std::string value, TYPE_TOKEN type, int startpos, int endpos);
        void BuildLiteralFloatToken(std::string value, int startpos, int endpos);
        void BuildLiteralIntToken(std::string value, int startpos, int endpos);

    private:
        bool IsKeywordToken(std::string value);
        bool IsTypeToken(std::string value);
        bool IsDelimiterToken(std::string value);
        bool IsArithmeticToken(std::string value);
        bool IsLogicalToken(std::string value);
        bool IsBoolLiteralToken(std::string value);
        bool IsStringScope(std::string value);
        bool IsCharacterScope(std::string value);

};