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
    for(char item : ALPHA::ALPHANUMERIC)
    {
        if(target == item)
        {
            return true;
        }
    }

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
       target == DELIMITERS::QUOTATION_MARKS     
      )
    {
        return true;
    }

    return false;
}

bool Lexer::IsArithmatic(char target)
{
    if(target == ARITHMETIC::ADD[0] || 
       target == ARITHMETIC::SUB[0] ||
       target == ARITHMETIC::DIV[0] ||
       target == ARITHMETIC::MUL[0] ||
       target == ARITHMETIC::MOD[0] ||
       target == ARITHMETIC::AND[0] ||
       target == ARITHMETIC::OR[0] ||
       target == ARITHMETIC::SHIFTLEFT[0] ||
       target == ARITHMETIC::SHIFTRIGHT[0])
    {
        return true;
    }

    return false;
}

bool Lexer::IsComparison(char target)
{
    if(target == COMPARISON::DIFF[0]   ||
       target == COMPARISON::EQUALS[0] ||
       target == COMPARISON::GREAT[0]  ||
       target == COMPARISON::LESS[0]   ||
       target == COMPARISON::GREATEQ[0]||
       target == COMPARISON::LESSEQ[0])
    {
        return true;
    }

    return false;
}

bool Lexer::IsLogical(char target)
{
    if(target == LOGICAL::AND[0] ||
       target == LOGICAL::OR[0])
    {
        return true;
    }

    return false;
}

bool Lexer::IsAttribution(char target)
{
    if(target == ATTRIBUTION::INCREMENT[0] ||
       target == ATTRIBUTION::DECREMENT[0])
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
    if(token == TYPE::NAME[TYPE::TNUMBER] ||
       token == TYPE::NAME[TYPE::TCHAR] ||
       token == TYPE::NAME[TYPE::TVOID] ||
       token == TYPE::NAME[TYPE::TBOOL] ||
       token == TYPE::NAME[TYPE::TTEXT]
      )
    {
        return new Token(token, NAME::TYPE);
    }

    return nullptr;
}

Token* Lexer::BindKeyword(std::string token)
{
    if(token == KEYWORDS::TVAR       ||
       token == KEYWORDS::TCONST     ||
       token == KEYWORDS::TFUN       ||
       token == KEYWORDS::TRETURN    ||
       token == KEYWORDS::TBREAK     ||
       token == KEYWORDS::TCONTINUE  ||
       token == KEYWORDS::TIF        ||
       token == KEYWORDS::TELIIF     ||
       token == KEYWORDS::TELSE      ||
       token == KEYWORDS::TFOR       ||
       token == KEYWORDS::TFOREACH   ||
       token == KEYWORDS::TWHILE     ||
       token == KEYWORDS::TDO        ||
       token == KEYWORDS::TIN        ||
       token == KEYWORDS::TAT        
       )
    {
        return new Token(token, NAME::KEYWORD);
    }

    return nullptr;
}

Token* Lexer::BindBoolean(std::string token)
{
    if(token == BOOLEAN_VALUE::TTRUE ||
       token == BOOLEAN_VALUE::TFALSE )
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
       token[0] == DELIMITERS::QUOTATION_MARKS     
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










