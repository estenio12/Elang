// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>

namespace AST
{
    static const uint8_t LOWORDERVALUE    = 0x1;
    static const uint8_t MIDORDERVALUE    = 0x5;
    static const uint8_t HIGHORDERVALUE   = 0xA;

    static const std::string HIGH_ORDER   = "(";
    static const std::string MID_ORDER[]  = {"*", "/"};
    static const std::string LOW_ORDER[]  = {"(", ")"};
    static const std::string DECAY_ORDER  = ")";

    const enum EMID_ORDER
    {
        MUL = 0,
        DIV = 1
    };

    const enum ELOW_ORDER
    {
        PLUS  = 0,
        MINUS = 1
    };

    class AST_Node
    {
        public:
            std::string Operator;
            std::string LeftContent;
            std::string RightContent;
            int PowerLevel = 0;

        public:
            void Reset()
            {
                this->Operator.clear();
                this->LeftContent.clear();
                this->RightContent.clear();
                this->PowerLevel = 0;
            }
    };
}