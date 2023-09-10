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

bool Lexer::IsAlphaNumetic(char letter)
{
    for(auto item : TEMPLATE::IS_ALPHA)
        if(item == letter) return true;

    return false;
}

void Lexer::Tokenize(std::string line)
{
    std::string buffer;
    int startpos = 0;
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
            if(IsDigit(line[i]))
                current_job = JOB_STATE::BUILD_DIGIT;
            
            if(IsAlphaNumetic(line[i]))
                current_job = JOB_STATE::BUILD_ALPHA_DIGIT;

            startpos = i + 1;
        }

        if(current_job == JOB_STATE::BUILD_DIGIT)
        {
            if(IsDigit(line[i]))
                buffer.push_back(line[i]);
            else
            {
                int endpos = i;

                if(IsDigitFloat(buffer))
                    this->BuildLiteralFloatToken(buffer, startpos, endpos);
                else
                    this->BuildLiteralIntToken(buffer, startpos, endpos);

                buffer.clear();
                current_job = JOB_STATE::UNDEFINED;
                i--;
            }
        }

        if(current_job == JOB_STATE::BUILD_ALPHA_DIGIT)
        {
            if(IsAlphaNumetic(line[i]))
                buffer.push_back(line[i]);
            else
            {
                int endpos = i;

                this->BindToken(buffer, startpos, endpos);

                buffer.clear();
                current_job = JOB_STATE::UNDEFINED;
                i--;
            }
        }
    }
}

void Lexer::BindToken(std::string value, int startpos, int endpos)
{
    if(IsKeyword(value)) this->BuildToken(value, TYPE_TOKEN::T_KEYWORD, startpos, endpos);
    else if(IsType(value)) this->BuildToken(value, TYPE_TOKEN::T_TYPE, startpos, endpos);
    else if(IsDelimiter(value)) this->BuildToken(value, TYPE_TOKEN::T_DELIMITER, startpos, endpos);
    else if(IsArithmetic(value)) this->BuildToken(value, TYPE_TOKEN::T_ARITHMETIC, startpos, endpos);
    else if(IsPrefix(value)) this->BuildToken(value, TYPE_TOKEN::T_PREFIX, startpos, endpos);
    else if(IsPostfix(value)) this->BuildToken(value, TYPE_TOKEN::T_POSTFIX, startpos, endpos);
    else if(IsLogical(value)) this->BuildToken(value, TYPE_TOKEN::T_LOGICAL, startpos, endpos);
    else if(IsBoolLiteral(value)) this->BuildToken(value, TYPE_TOKEN::T_BOOL_LITERAL, startpos, endpos);
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

bool Lexer::IsKeyword(std::string value)
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

bool Lexer::IsType(std::string value)
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

bool Lexer::IsDelimiter(std::string value)
{
    if(value == DELIMITER::T_COLON           ||
       value == DELIMITER::T_COMMA           ||
       value == DELIMITER::T_OPEN_BRACKET    ||
       value == DELIMITER::T_CLOSE_BRACKET   ||
       value == DELIMITER::T_OPEN_BRANCE     ||
       value == DELIMITER::T_CLOSE_BRACE     ||
       value == DELIMITER::T_OPEN_PARAM      ||
       value == DELIMITER::T_CLOSE_PARAM     ||
       value == DELIMITER::T_QUOTATION_MARKS ||
       value == DELIMITER::T_APHOSTROFE      ||
       value == DELIMITER::T_ASSIGN          ||
       value == DELIMITER::T_EOF             )
    {
        return true;
    }

    return false;
}

bool Lexer::IsArithmetic(std::string value)
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
       value == ARITHMETIC::T_SHIFT_RIGHT ||
       value == ARITHMETIC::T_SHIFT_LEFT  )
    {
        return true;
    }

    return false;
}

bool Lexer::IsPrefix(std::string value)
{
    if(value == PREFIX::T_PLUS_PLUS    ||
       value == PREFIX::T_MINUS_MINUS    )
    {
        return true;
    }

    return false;
}

bool Lexer::IsPostfix(std::string value)
{
    if(value == POSTFIX::T_PLUS_PLUS    ||
       value == POSTFIX::T_MINUS_MINUS    )
    {
        return true;
    }

    return false;
}

bool Lexer::IsLogical(std::string value)
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

bool Lexer::IsBoolLiteral(std::string value)
{
    if(value == TEMPLATE::TRUE_LITERAL    ||
       value == TEMPLATE::FALSE_LITERAL   )
    {
        return true;
    }

    return false;
}
