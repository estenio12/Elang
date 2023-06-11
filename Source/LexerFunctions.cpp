#include "../Include/LexicalAnalyser.hpp"

bool Lexer::IsDigit(char target)
{
    for(char item : DIGIT::DIGIT)
    {
        if(item == target) return true;
    }

    return false;
}

bool Lexer::IsAlpha(char target)
{
    // std::cout << "...........Debug IsAlpha char: " << target << "\n";
    for(char item : ALPHA::ALPHANUMERIC)
    {
        if(target == item)
        {
            // std::cout << "...........Debug IsAlpha char result: verdadeiro" << "\n";
            return true;
        }
    }

    // std::cout << "...........Debug IsAlpha char result: falso" << "\n";
    return false;
}

bool Lexer::IsDelimiter(char target)
{
    if(target == DELIMITERS::EOL                 ||
       target == DELIMITERS::COLON               ||
       target == DELIMITERS::ASSIGN              ||
       target == DELIMITERS::OPEN_PARAM          ||
       target == DELIMITERS::CLOSE_PARAM         ||
       target == DELIMITERS::OPEN_BRACE          ||
       target == DELIMITERS::CLOSE_BRACE         ||
       target == DELIMITERS::OPEN_SQUAREBRACKET  ||
       target == DELIMITERS::CLOSE_SQUAREBRACKET ||
       target == DELIMITERS::COMMA               ||
       target == DELIMITERS::APOSTROPHE          ||
       target == DELIMITERS::QUOTATION_MARKS     ||
       target == DELIMITERS::BACK_SLASH
      )
    {
        return true;
    }

    return false;
}

Token* Lexer::BindToken(std::string token)
{
    Token* tempToken;

    // # Check type
    tempToken = this->BindType(token);
    if(tempToken != nullptr) return tempToken;

    // # Check keyword
    tempToken = this->BindKeyword(token);
    if(tempToken != nullptr) return tempToken;

    // # Check boolean values
    tempToken = this->BindBoolean(token);
    if(tempToken != nullptr) return tempToken;

    // # Check delimiters
    tempToken = this->BindDelimiters(token);
    if(tempToken != nullptr) return tempToken;

    // # Return a identifier
    return new Token(token, NAME::IDENTIFIER);
}

Token* Lexer::BindType(std::string token)
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

Token* Lexer::BindKeyword(std::string token)
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

Token* Lexer::BindBoolean(std::string token)
{
    if(token == BOOLEAN_VALUE::TRUE ||
       token == BOOLEAN_VALUE::FALSE )
    {
        return new Token(token, NAME::BOOLEAN);
    }

    return nullptr;
}

Token* Lexer::BindDelimiters(std::string token)
{
    if(token[0] == DELIMITERS::EOL                 ||
       token[0] == DELIMITERS::COLON               ||
       token[0] == DELIMITERS::ASSIGN              ||
       token[0] == DELIMITERS::OPEN_PARAM          ||
       token[0] == DELIMITERS::CLOSE_PARAM         ||
       token[0] == DELIMITERS::OPEN_BRACE          ||
       token[0] == DELIMITERS::CLOSE_BRACE         ||
       token[0] == DELIMITERS::OPEN_SQUAREBRACKET  ||
       token[0] == DELIMITERS::CLOSE_SQUAREBRACKET ||
       token[0] == DELIMITERS::COMMA               ||
       token[0] == DELIMITERS::APOSTROPHE          ||
       token[0] == DELIMITERS::QUOTATION_MARKS     ||
       token[0] == DELIMITERS::BACK_SLASH
      )
    {
        return new Token(token, NAME::DELIMITER);
    }

    return nullptr;
}

void Lexer::ThrowError(std::string msg, int position = 0)
{
    Output::PrintError("Line: " + std::to_string(this->lineCounter) + ":" + std::to_string(position) +" | " + msg);
    exit(EXIT_FAILURE);
}










