#include "../Include/LexicalAnalyser.hpp"

bool Lexer::IsDigit(char* target)
{
    for(char item : DIGIT::DIGIT)
    {
        if(item == *target) return true;
    }

    return false;
}

Token* Lexer::BindToken(std::string token)
{
    Token* tempToken;

    // # Check type
    tempToken = this->IsType(token);
    if(tempToken != nullptr) return tempToken;

    // # Check keyword
    tempToken = this->IsKeyword(token);
    if(tempToken != nullptr) return tempToken;

    // # Check boolean values
    tempToken = this->IsBoolean(token);
    if(tempToken != nullptr) return tempToken;

    // # Return a identifier
    return new Token(token, NAME::IDENTIFIER);
}

Token* Lexer::IsType(std::string token)
{
    if(token == TYPE::NAME[TYPE::NUMBER] ||
       token == TYPE::NAME[TYPE::CHAR] ||
       token == TYPE::NAME[TYPE::VOID] ||
       token == TYPE::NAME[TYPE::BOOL] ||
       token == TYPE::NAME[TYPE::TEXT]
      )
    {
        return new Token(token, NAME::TYPE);
    }

    return nullptr;
}

Token* Lexer::IsKeyword(std::string token)
{
    if(token == KEYWORDS::VAR       ||
       token == KEYWORDS::CONST     ||
       token == KEYWORDS::FUN       ||
       token == KEYWORDS::RETURN    ||
       token == KEYWORDS::BREAK     ||
       token == KEYWORDS::CONTINUE
       )
    {
        return new Token(token, NAME::KEYWORD);
    }

    return nullptr;
}

Token* Lexer::IsBoolean(std::string token)
{
    if(token == BOOLEAN_VALUE::TRUE ||
       token == BOOLEAN_VALUE::FALSE )
    {
        return new Token(token, NAME::BOOLEAN);
    }

    return nullptr;
}














