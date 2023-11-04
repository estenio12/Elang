#include "../headers/lexer.hpp"

Lexer::Lexer(std::string sourcePath):sourcePath(sourcePath)
{
    this->fileHanler.open(sourcePath);
}

Lexer::~Lexer(){}

Token* Lexer::GetNextToken()
{
    if((tokenPool.empty() || tokenPool.size() <= 2) && !this->fileHanler.eof())
        this->LoadMoreToken();

    if(!tokenPool.empty())
    {
        auto token = tokenPool.front();
        tokenPool.pop();
        
        return token;
    }

    fileHanler.close();
    return nullptr;
}

std::string Lexer::Sanitaze(std::string line)
{
    bool stringUp = false;
    std::string buffer;
    const char COMMENTARY = '#';

    for(auto letter : line)
    {
        // # check if is string scope
        if(letter == DELIMITER::T_QUOTATION_MARKS[0])
            stringUp = !stringUp;

        if(!stringUp && letter == COMMENTARY)
            return buffer;
        else
            buffer.push_back(letter);
    }

    return buffer;
}

void Lexer::LoadMoreToken()
{
    try
    {
        std::string line;
        std::getline(this->fileHanler, line);
        this->lineCounter++;

        line = Sanitaze(line);

        if(!fileHanler.eof() && line.empty()) 
            LoadMoreToken();

        if(!line.empty()) 
            this->Tokenize(line);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Lexer::CheckOutOfMemoryBuildToken(Token* token)
{
    if(token == nullptr)
    {
        Output::PrintCustomizeError("fatal error: ", "out of memory in tokenize operation.");
        exit(EXIT_FAILURE);
    }
}

bool Lexer::IsDigit(char letter)
{
    for(auto item : TEMPLATE::IS_DIGIT)
        if(item == letter) return true;

    return false;
}

bool Lexer::IsDigitFloat(std::string buffer)
{
    return buffer.find('.') != std::string::npos;
}

bool Lexer::IsAlpha(char letter)
{
    for(auto item : TEMPLATE::IS_ALPHA)
        if(item == letter) return true;

    return false;
}

bool Lexer::IsAlphaNumetic(char letter)
{
    for(auto item : TEMPLATE::IS_ALPHA_NUMERIC)
        if(item == letter) return true;

    return false;
}

void Lexer::Tokenize(std::string line)
{
    std::string buffer;
    int current_job = JOB_STATE::UNDEFINED;

    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == SKIP_CHARACTER::TABULATION ||
           line[i] == SKIP_CHARACTER::RETURN     ||
           line[i] == SKIP_CHARACTER::NEWLINE    )
        {
            continue;
        }
        
        if(current_job == JOB_STATE::UNDEFINED)
        {
            if(IsDelimiter({line[i], line[i + 1]}))
            {
                int startpos = i + 1;
                int endpos   = i + 1;
                BuildToken({line[i]}, TYPE_TOKEN::T_DELIMITER, startpos, endpos);
                buffer.clear();
                continue;
            }

            if(IsSelfIncrementation({line[i], line[i + 1]}))
            {
                int startpos = i + 1;
                int endpos   = i + 2;
                this->BuildToken({line[i], line[i + 1]}, GetTypeSelfIncrementation(), startpos, endpos);
                buffer.clear();
                // # If self increment or decrement symbol use the two character, then, 'i' counter will jump the next character.
                i++;
                continue;
            }

            auto arithmetic = IsArithmetic({line[i], line[i + 1]});
            if(arithmetic != 0)
            {
                int startpos = i + 1;
                int endpos   = i + 1;
                std::string tempToken;

                if(arithmetic == 1)
                    tempToken = {line[i]};
                else
                {
                    tempToken = {line[i], line[i + 1]};
                    endpos++;
                }

                this->BuildToken(tempToken, TYPE_TOKEN::T_ARITHMETIC, startpos, endpos);
                buffer.clear();

                // # If arithmetic symbol use the two character, then, 'i' counter will jump the next character.
                if(arithmetic == 2) i++;

                continue;
            }

            auto logical = IsLogical({line[i], line[i + 1]});
            if(logical != 0)
            {
                int startpos = i + 1;
                int endpos   = i + 1;
                std::string tempToken;

                if(logical == 1)
                    tempToken = {line[i]};
                else
                {
                    tempToken = {line[i], line[i + 1]};
                    endpos++;
                }

                this->BuildToken(tempToken, TYPE_TOKEN::T_LOGICAL, startpos, endpos);
                buffer.clear();

                // # If logical symbol use the two character, then, 'i' counter will jump the next character.
                if(logical == 2) i++;

                continue;
            }

            if(IsDigit(line[i]))
            {
                // Output::PrintDebug("Entrei");
                current_job = JOB_STATE::BUILD_DIGIT;
            }
            
            if(IsAlpha(line[i]))
            {
                current_job = JOB_STATE::BUILD_ALPHA_DIGIT;
            }
        }

        if(current_job == JOB_STATE::BUILD_DIGIT)
        {
            if(IsDigit(line[i]))
                buffer.push_back(line[i]);
            else
            {
                int startpos = i - (buffer.size() - 1);
                int endpos   = i;

                if(IsDigitFloat(buffer))
                    this->BuildLiteralFloatToken(buffer, startpos, endpos);
                else
                    this->BuildLiteralIntToken(buffer, startpos, endpos);

                buffer.clear();
                current_job = JOB_STATE::UNDEFINED;

                if(line[i] != SKIP_CHARACTER::WHITESPACE) i--;
            }
        }

        if(current_job == JOB_STATE::BUILD_ALPHA_DIGIT)
        {
            if(IsAlphaNumetic(line[i]))
            {
                buffer.push_back(line[i]);
            }
            else
            {
                int startpos = i - (buffer.size() - 1);
                int endpos   = i;

                this->BindToken(buffer, startpos, endpos);

                buffer.clear();
                current_job = JOB_STATE::UNDEFINED;

                if(line[i] != SKIP_CHARACTER::WHITESPACE) i--;
            }
        }

        // # Check if next character is end of string '\0' and buffer has content to tokenize
        if(line[i + 1] == '\0' && buffer.length() > 0)
        {
            int startpos = i - (buffer.size() - 2);
            int endpos   = i + 1;

            this->BindToken(buffer, startpos, endpos);

            buffer.clear();
            current_job = JOB_STATE::UNDEFINED;
        }
    }
}

void Lexer::BindToken(std::string value, int startpos, int endpos)
{
    if(IsKeywordToken(value)) this->BuildToken(value, TYPE_TOKEN::T_KEYWORD, startpos, endpos);
    else if(IsTypeToken(value)) this->BuildToken(value, TYPE_TOKEN::T_TYPE, startpos, endpos);
    else if(IsDelimiterToken(value)) this->BuildToken(value, TYPE_TOKEN::T_DELIMITER, startpos, endpos);
    else if(IsArithmeticToken(value)) this->BuildToken(value, TYPE_TOKEN::T_ARITHMETIC, startpos, endpos);
    else if(IsLogicalToken(value)) this->BuildToken(value, TYPE_TOKEN::T_LOGICAL, startpos, endpos);
    else if(IsBoolLiteralToken(value)) this->BuildToken(value, TYPE_TOKEN::T_BOOL_LITERAL, startpos, endpos);
    else this->BuildToken(value, TYPE_TOKEN::T_IDENTIDIER, startpos, endpos);
}

void Lexer::BuildLiteralFloatToken(std::string value, int startpos, int endpos)
{
    auto token = new Token
    (
        this->lineCounter,
        startpos,
        endpos,
        value,
        TYPE_TOKEN::T_FLOAT_LITERAL
    );

    CheckOutOfMemoryBuildToken(token);

    this->tokenPool.push(token);
}

void Lexer::BuildLiteralIntToken(std::string value, int startpos, int endpos)
{
    auto token = new Token
    (
        this->lineCounter,
        startpos,
        endpos,
        value,
        TYPE_TOKEN::T_INT_LITERAL
    );

    CheckOutOfMemoryBuildToken(token);

    this->tokenPool.push(token);
}

void Lexer::BuildToken(std::string value, TYPE_TOKEN type, int startpos, int endpos)
{
    auto token = new Token
    (
        this->lineCounter,
        startpos,
        endpos,
        value,
        type
    );

    CheckOutOfMemoryBuildToken(token);

    this->tokenPool.push(token);
}

bool Lexer::IsKeywordToken(std::string value)
{
    if(value == KEYWORD::T_ARRAY    ||
       value == KEYWORD::T_BREAK    ||
       value == KEYWORD::T_CONST    ||
       value == KEYWORD::T_CONTINUE ||
       value == KEYWORD::T_ELSE     ||
       value == KEYWORD::T_END      ||
       value == KEYWORD::T_FOR      ||
       value == KEYWORD::T_FUN      ||
       value == KEYWORD::T_IF       ||
       value == KEYWORD::T_RETURN   ||
       value == KEYWORD::T_VAR      ||
       value == KEYWORD::T_WHILE    )
    {
        return true;
    }

    return false;
}

bool Lexer::IsTypeToken(std::string value)
{
    if(value == TYPE::T_BOOL   ||
       value == TYPE::T_CHAR   ||
       value == TYPE::T_FLOAT  ||
       value == TYPE::T_INT    ||
       value == TYPE::T_STRING ||
       value == TYPE::T_VOID   )
    {
        return true;
    }

    return false;
}

bool Lexer::IsDelimiterToken(std::string value)
{
    if(value == DELIMITER::T_COLON           ||
       value == DELIMITER::T_COMMA           ||
       value == DELIMITER::T_OPEN_BRACKET    ||
       value == DELIMITER::T_CLOSE_BRACKET   ||
       value == DELIMITER::T_OPEN_BRANCE     ||
       value == DELIMITER::T_CLOSE_BRACE     ||
       value == DELIMITER::T_OPEN_PAREM      ||
       value == DELIMITER::T_CLOSE_PAREM     ||
       value == DELIMITER::T_QUOTATION_MARKS ||
       value == DELIMITER::T_APHOSTROFE      ||
       value == DELIMITER::T_EOF             )
    {
        return true;
    }

    return false;
}

bool Lexer::IsArithmeticToken(std::string value)
{
    if(value == ARITHMETIC::T_PLUS        ||
       value == ARITHMETIC::T_MINUS       ||
       value == ARITHMETIC::T_DIV         ||
       value == ARITHMETIC::T_MUL         ||
       value == ARITHMETIC::T_MOD         ||
       value == ARITHMETIC::T_PLUS_EQ     ||
       value == ARITHMETIC::T_MINUS_EQ    ||
       value == ARITHMETIC::T_DIV_EQ      ||
       value == ARITHMETIC::T_MUL_EQ      ||
       value == ARITHMETIC::T_OR          ||
       value == ARITHMETIC::T_AND         ||
       value == ARITHMETIC::T_POW         ||
       value == ARITHMETIC::T_SHIFT_RIGHT ||
       value == ARITHMETIC::T_SHIFT_LEFT  )
    {
        return true;
    }

    return false;
}

bool Lexer::IsLogicalToken(std::string value)
{
    if(value == LOGICAL::T_GREAT_THEN    ||
       value == LOGICAL::T_LESS_THEN     ||
       value == LOGICAL::T_GREAT_THEN_EQ ||
       value == LOGICAL::T_LESS_THEN_EQ  ||
       value == LOGICAL::T_OR            ||
       value == LOGICAL::T_AND           ||
       value == LOGICAL::T_DIFF          ||
       value == LOGICAL::T_EQUALS        )
    {
        return true;
    }


    return false;
}

bool Lexer::IsBoolLiteralToken(std::string value)
{
    if(value == TEMPLATE::TRUE_LITERAL    ||
       value == TEMPLATE::FALSE_LITERAL   )
    {
        return true;
    }

    return false;
}

bool Lexer::IsDelimiter(std::string value)
{
    // # IN CURRENT VERSION OF COMPILER, DELIMITER DOES NOT HAVE MORE THE ONE CHARACTER
    if(value.size() > 1) value.pop_back();

    if(value == DELIMITER::T_COLON           ||
       value == DELIMITER::T_COMMA           ||
       value == DELIMITER::T_OPEN_BRACKET    ||
       value == DELIMITER::T_CLOSE_BRACKET   ||
       value == DELIMITER::T_OPEN_BRANCE     ||
       value == DELIMITER::T_CLOSE_BRACE     ||
       value == DELIMITER::T_OPEN_PAREM      ||
       value == DELIMITER::T_CLOSE_PAREM     ||
       value == DELIMITER::T_QUOTATION_MARKS ||
       value == DELIMITER::T_APHOSTROFE      ||
       value == DELIMITER::T_ASSIGN          ||
       value == DELIMITER::T_EOF             )
    {
        return true;
    }

    return false;
}

int Lexer::IsArithmetic(std::string value)
{
    if(value[1] != ARITHMETIC::T_PLUS_EQ[1]     &&
       value[1] != ARITHMETIC::T_SHIFT_LEFT[1]  &&
       value[1] != ARITHMETIC::T_SHIFT_RIGHT[1] &&
       value != LOGICAL::T_OR                   &&
       value != LOGICAL::T_AND                  ) 
    {
        value.pop_back();
    }

    if(value == ARITHMETIC::T_PLUS   ||
       value == ARITHMETIC::T_MINUS  ||
       value == ARITHMETIC::T_DIV    ||
       value == ARITHMETIC::T_MUL    ||
       value == ARITHMETIC::T_MOD    ||
       value == ARITHMETIC::T_OR     ||
       value == ARITHMETIC::T_AND    )
    {
        return 1;
    }

    if(value == ARITHMETIC::T_PLUS_EQ     ||
       value == ARITHMETIC::T_MINUS_EQ    ||
       value == ARITHMETIC::T_DIV_EQ      ||
       value == ARITHMETIC::T_MUL_EQ      ||
       value == ARITHMETIC::T_SHIFT_RIGHT ||
       value == ARITHMETIC::T_SHIFT_LEFT  )
    {
        return 2;
    }

    return 0;
}

TYPE_TOKEN Lexer::GetTypeSelfIncrementation()
{
    auto token = this->tokenPool.back();

    if(token != nullptr && 
      (token->type == TYPE_TOKEN::T_IDENTIDIER  || 
       token->value == DELIMITER::T_CLOSE_PAREM )
      )
    {
        return TYPE_TOKEN::T_POSTFIX;
    }

    return TYPE_TOKEN::T_PREFIX;
}

bool Lexer::IsSelfIncrementation(std::string value)
{
    if(value == SELF_INCREMENTATION::T_MINUS_MINUS ||
       value == SELF_INCREMENTATION::T_PLUS_PLUS   )
    {
        return true;
    }

    return false;
}

int Lexer::IsLogical(std::string value)
{
    if(value[1] != LOGICAL::T_GREAT_THEN_EQ[1] &&
       value[1] != LOGICAL::T_OR[1]            &&
       value[1] != LOGICAL::T_AND[1]           ) 
    {
        value.pop_back();
    }

    if(value == LOGICAL::T_GREAT_THEN ||
       value == LOGICAL::T_LESS_THEN  )
    {
        return 1;
    }

    if(value == LOGICAL::T_GREAT_THEN_EQ ||
       value == LOGICAL::T_LESS_THEN_EQ  ||
       value == LOGICAL::T_OR            ||
       value == LOGICAL::T_AND           ||
       value == LOGICAL::T_DIFF          ||
       value == LOGICAL::T_EQUALS        )
    {
        return 2;
    }

    return 0;
}

