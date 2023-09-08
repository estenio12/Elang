///////////////////////////
// @author: Estenio Garcia
// @license: Apache 2.0
// @copyright: all
///////////////////////////

#pragma once

#include <queue>
#include "./definitions/token-definition.hpp"
#include "./models/token.hpp"

class Lexer
{
    private:
        std::queue<Token*> tokenPoll;

    public:
        Lexer();
        ~Lexer();

    public:
        Token* GetNextToken();

};