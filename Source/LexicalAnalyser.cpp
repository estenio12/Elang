#include "../Include/LexicalAnalyser.hpp"

Lexer::Lexer(std::string sourceCodePath)
{
    this->tools   = new Tools();

    this->fileHandler.open(sourceCodePath, std::ios::binary);
}

Lexer::~Lexer(){}

Token* Lexer::GetNextToken()
{
    return this->GetToken();
}

Token* Lexer::GetToken()
{
    if(this->tokenList.size() <= 0)
        this->LoadLineFromFile();

    if(this->tokenList.size() > 0)
    {
        auto token = this->tokenList.at(0);
        this->tokenList.erase(tokenList.begin());

        return token;
    }

    return nullptr;
}

void Lexer::LoadLineFromFile()
{
    try
    {
        std::string line;
        std::getline(this->fileHandler, line);
        this->lineCounter++;

        this->Tokenize(line);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Lexer::Tokenize(std::string line)
{
    int startPos = 0;
    int endPos   = 0;
    std::string current = NAME::UNDEFINED;

    for(int i = 0; i < line.size(); i++)
    {
        // # Skip Characters
        if(this->IsSkipCharacter(&line[i])) continue;

        // # Check if is digits
        if(this->IsDigit(&line[i]) && 
          (current == NAME::UNDEFINED || current == NAME::NUMBER))
        {
            if(current == NAME::UNDEFINED) startPos = i;

            current  = NAME::NUMBER;
            
            if(!this->IsDigit(&line[i + 1]))
            {
                endPos = i + 1;
                std::string token = line.substr(startPos, endPos);
                this->BuildToken(token, NAME::NUMBER, startPos, endPos);

                // # Reset
                current  = NAME::UNDEFINED;
                startPos = 0;
                endPos   = 0;
            }
            
            continue;
        }
    
        // # Check if is char
        
    }
}

bool Lexer::IsSkipCharacter(char* target)
{
    for(char item : DELIMITERS::SKIP_CHAR)
    {
        if(*target == item)
        {
            return true;
        }
    }

    return false;
}

void Lexer::BuildToken(std::string value, std::string type, int startPos, int endPos)
{
    auto token = new Token
    (
        value, type, this->lineCounter, startPos, endPos
    );

    this->tokenList.push_back(token);
}








