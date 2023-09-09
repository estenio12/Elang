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
        std::string Sanitaze(std::string line);

    private:
        void Tokenize(std::string line);
        void CheckOutOfMemoryBuildToken(Token*);

    private:
        void BindToken(std::string value, int startpos, int endpos);

    private:
        bool IsDigit(char letter);
        bool IsDigitFloat(std::string buffer);
        bool IsAlphaNumetic(char letter);

    private:
        void BuildToken(std::string value, TYPE_TOKEN type, int startpos, int endpos);
        void BuildLiteralFloatToken(std::string value, int startpos, int endpos);
        void BuildLiteralIntToken(std::string value, int startpos, int endpos);

    private:
        bool IsKeyword(std::string value);
        bool IsType(std::string value);
        bool IsDelimiter(std::string value);
        bool IsArithmetic(std::string value);
        bool IsPrefix(std::string value);
        bool IsPostfix(std::string value);
        bool IsLogical(std::string value);
        bool IsFloatLiteral(std::string value);
        bool IsIntLiteral(std::string value);
        bool IsCharLiteral(std::string value);
        bool IsBoolLiteral(std::string value);
};