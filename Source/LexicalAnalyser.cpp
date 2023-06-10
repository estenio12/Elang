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
    if(this->tokenList.empty() || this->tokenList.size() <= 1) 
    {  
        this->LoadLineFromFile();
    }

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
    std::string current    = NAME::UNDEFINED;
    std::string buildToken = "";
    
    for(int i = 0; i < line.size(); i++)
    {
        if(current == NAME::UNDEFINED)
        {
            if(this->IsDigit(line[i]))
            {
                startPos = i;
                current  = NAME::NUMBER;
                buildToken.push_back(line[i]);
                
                continue;
            }
        
            if(this->IsAlpha(line[i]))
            {
                startPos = i;
                current  = NAME::BUILDING;
                buildToken.push_back(line[i]);

                continue;
            }

            if(this->IsDelimiter(line[i]))
            {
                // # Prepare Token
                auto token      = this->BindToken(this->ConvertToChar(line[i]));
                token->startPos = i;
                token->line     = this->lineCounter;
                token->endPos   = i;

                // # Insert to list
                this->tokenList.push_back(token);

                // # Reset
                buildToken.clear();
                startPos = 0;
                current  = NAME::UNDEFINED;

                continue;
            }
        }
    
        if(current == NAME::NUMBER)
        {
            if(this->IsDigit(line[i]))
            {
                buildToken.push_back(line[i]);
            }

            if(!this->IsDigit(line[i + 1]))
            {
                // # Prepare Token
                this->BuildToken(buildToken, NAME::NUMBER, startPos, buildToken.size());

                // # Reset
                buildToken.clear();
                startPos = 0;
                current = NAME::UNDEFINED;
            }
        }
    
        if(current == NAME::BUILDING)
        {
            if(this->IsAlpha(line[i]))
            {
                buildToken.push_back(line[i]);
            }

            if(!this->IsAlpha(line[i + 1]))
            {
                // # Prepare Token
                auto token = this->BindToken(buildToken);
                token->startPos = startPos;
                token->line     = this->lineCounter;
                token->endPos   = buildToken.size();

                // # Insert to list
                this->tokenList.push_back(token);

                // # Reset
                buildToken.clear();
                startPos = 0;
                current = NAME::UNDEFINED;
            }
        }
    }
}

void Lexer::BuildToken(std::string value, std::string type, int startPos, int endPos)
{
    auto token = new Token
    (
        value, type, this->lineCounter, startPos, endPos
    );

    this->tokenList.push_back(token);
}

std::string Lexer::ConvertToChar(char target)
{
    std::string nstring;
    nstring.push_back(target);

    return nstring;
}




