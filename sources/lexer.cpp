#include "../headers/lexer.hpp"

Lexer::Lexer(std::string sourcePath):sourcePath(sourcePath)
{
    this->LoadFileHandler();
}

Lexer::~Lexer(){}

Token* Lexer::GetNextToken()
{
    auto token = this->tokenPool.front();

    if(token != nullptr)
    {
        this->tokenPool.pop();

        if(this->tokenPool.size() <= MIN_POOL_SIZE)
            this->LoadMoreToken();

        return token;
    }

    return nullptr;
}

bool Lexer::IsValidPath()
{
    if(this->sourcePath.empty()) return false;
    return std::filesystem::exists(std::filesystem::path(this->sourcePath));
}

std::string Lexer::RemoveCommentary(std::string line)
{
    const char COMMENTED_FLAG = '#';
    int range = 0;

    for(range = 0; range < line.size(); range++)
        if(line[range] == COMMENTED_FLAG) break;

    return line.substr(0, range);
}

void Lexer::LoadFileHandler()
{
    if(this->IsValidPath())
    {
        this->fileHanler.open(sourcePath);
        LoadFirstTokenPool();
    }
    else
    {
        Output::PrintCustomizeError("Fatal Error: ", "source file not found!");
        exit(EXIT_FAILURE);
    }
}

std::string Lexer::ReadLine()
{
    std::string line;
    std::getline(this->fileHanler, line);
    this->lineCounter++;
    return line;
}

void Lexer::LoadMoreToken()
{
    auto line = this->RemoveCommentary(this->ReadLine());

    if(!this->endTokenize)
    {
        if(line.empty())
            this->LoadMoreToken();
        else if(this->fileHanler.eof())
        {
            this->endTokenize = true;
            this->fileHanler.close();
        }
        else
            this->Tokenize(line);
    }
}

void Lexer::Tokenize(std::string line)
{
    Output::PrintDebug(line);
}

void Lexer::LoadFirstTokenPool()
{
    this->LoadMoreToken();
}



