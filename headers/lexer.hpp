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
        void LoadFirstTokenPool();
        bool IsValidPath();
        std::string RemoveCommentary(std::string line);
        std::string ReadLine();

    private:
        void Tokenize(std::string line);

};