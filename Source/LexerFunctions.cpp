#include "../Include/LexicalAnalyser.hpp"

bool Lexer::IsDigit(char* target)
{
    for(char item : DIGIT::DIGIT)
    {
        if(item == *target) return true;
    }

    return false;
}




















