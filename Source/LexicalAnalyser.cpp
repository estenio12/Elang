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
            if(this->IsDelimiter(line[i]))
            {
                if(line[i] == DELIMITERS::QUOTATION_MARKS)
                {
                    current = NAME::STRING;
                    continue;
                }
                // # Check if char value
                else if(line[i] == DELIMITERS::APOSTROPHE)
                {
                    if(line[i] == DELIMITERS::APOSTROPHE && 
                       line[i + 2] == DELIMITERS::APOSTROPHE)
                    {
                        // # Build Token
                        this->BuildToken(this->ConvertToString(line[i + 1]),
                                         NAME::CHARACTER, i + 1, i + 1);
                        i += 2;
                    }
                    else
                    {
                        this->ThrowError("Syntax error in char value declaration! the Apostrophe open but never closes.", i + 1);
                    }
                }
                else
                {
                    // # Prepare Token
                    auto token      = this->BindToken(this->ConvertToString(line[i]));
                    token->startPos = i;
                    token->line     = this->lineCounter;
                    token->endPos   = i;

                    // # Insert to list
                    this->tokenList.push_back(token);
                }

                // # Reset
                buildToken.clear();
                startPos = 0;
                current  = NAME::UNDEFINED;

                continue;
            }

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

            if(this->IsDelimiter(line[i]))
            {
                if(line[i] == DELIMITERS::QUOTATION_MARKS)
                {
                    current = NAME::STRING;
                    continue;
                }
                // # Check if char value
                else if(line[i] == DELIMITERS::APOSTROPHE)
                {
                    if(line[i] == DELIMITERS::APOSTROPHE && 
                       line[i + 2] == DELIMITERS::APOSTROPHE)
                    {
                        // # Build Token
                        this->BuildToken(this->ConvertToString(line[i + 1]),
                                         NAME::CHARACTER, i + 1, i + 1);
                        i += 2;
                    }
                    else
                    {
                        this->ThrowError("Syntax error in char value declaration! the Apostrophe open but never closes.", i + 1);
                    }
                }
                else
                {
                    // # Prepare Token
                    auto token      = this->BindToken(this->ConvertToString(line[i]));
                    token->startPos = i;
                    token->line     = this->lineCounter;
                    token->endPos   = i;

                    // # Insert to list
                    this->tokenList.push_back(token);
                }

                // # Reset
                buildToken.clear();
                startPos = 0;
                current  = NAME::UNDEFINED;

                continue;
            }
        }
    
        if(current == NAME::STRING)
        {
            if(line[i + 1] == DELIMITERS::_EOF &&
               line[i] != DELIMITERS::QUOTATION_MARKS)
            {
                this->ThrowError("Syntax error in string declaration! The quotes open but never close.", i + 1);
            }

            if(line[i] == DELIMITERS::QUOTATION_MARKS)
            {
                this->BuildToken(buildToken, NAME::STRING, startPos, i + 1);

                // # Reset
                buildToken.clear();
                startPos = 0;
                current  = NAME::UNDEFINED;
            }
            else
            {
                buildToken.push_back(line[i]);
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

std::string Lexer::ConvertToString(char target)
{
    std::string nstring;
    nstring.push_back(target);

    return nstring;
}




