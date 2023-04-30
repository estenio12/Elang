#include "../Include/Compiler.hpp"

Compiler::Compiler(std::string path):path(path)
{
    this->lexer  = new Lexer();
    this->parser = new Parser(&this->lineCounter);
}

Compiler::~Compiler(){}

void Compiler::CheckIfFileExist()
{
    if(!std::filesystem::exists(std::filesystem::path(this->path)))
    {
        Output::PrintCustomizeError("Fatal Error: ", "File cannot be found!");
        exit(EXIT_FAILURE);
    }
}

void Compiler::Run()
{
    this->CheckIfFileExist();

    try
    {
        std::string line;
        this->fileHandle.open(this->path, std::ios::in);

        if(this->fileHandle.is_open() && this->fileHandle.good())
        {
            while(std::getline(this->fileHandle, line))
            {
                lineCounter++;

                if(Checker::IsValidLine(line))
                {
                    auto newline = this->SanitizeLine(line); 
                    auto Tlist   = this->lexer->Tokenize(newline);
                    
                    if(this->parser->Parse(Tlist))
                    {

                    }                         
                }
            }
        }
        else
        {
            Output::PrintError("File cannot be read!");
            exit(EXIT_FAILURE);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

std::string Compiler::SanitizeLine(std::string line)
{
    std::string nline;

    for(int i = 0; i < line.size(); i++)
    {
       if(i == 0 && line[0] == DELIMITERS::WHITESPACE[0] ||
          line[i] == DELIMITERS::WHITESPACE[0] && 
          line[i - 1] == DELIMITERS::WHITESPACE[0] )
       {
            continue;
       }
       else
       {
            if((i + 1) < line.size())
            {
                if(line[i] == DELIMITERS::BACK_SLASH[0] &&
                   line[i + 1] == DELIMITERS::BACK_SLASH[0])
                {
                    return nline;
                }
            }

            if(line[i] != DELIMITERS::NEWLINE[0] &&
               line[i] != DELIMITERS::RETURNING[0] &&
               line[i] != DELIMITERS::TABULATION[0])
            {
                nline.push_back(line[i]);
            }
       }
        
    }

    return nline;
}