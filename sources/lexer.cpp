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

    // Output::PrintDebug(std::to_string(tokenPool.size()));
    // Output::PrintDebug(line);
}

void Lexer::BindToken(std::string value, int startpos, int endpos)
{


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
    

    return false;
}

bool Lexer::IsType(std::string value)
{
    

    return false;
}

bool Lexer::IsDelimiter(std::string value)
{
    

    return false;
}

bool Lexer::IsArithmetic(std::string value)
{
    

    return false;
}

bool Lexer::IsPrefix(std::string value)
{
    

    return false;
}

bool Lexer::IsPostfix(std::string value)
{
    

    return false;
}

bool Lexer::IsLogical(std::string value)
{
    

    return false;
}

bool Lexer::IsFloatLiteral(std::string value)
{
    

    return false;
}

bool Lexer::IsIntLiteral(std::string value)
{
    

    return false;
}

bool Lexer::IsCharLiteral(std::string value)
{
    

    return false;
}

bool Lexer::IsBoolLiteral(std::string value)
{
    

    return false;
}
