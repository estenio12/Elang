#include "../Includes/Compiler.hpp"

Compiler::Compiler(char** Path)
{
    this->FilePathSource = Path[1];
    this->FilePathOutput = "./Test/App.html";

    this->lexer  = new Lexer();
    this->parser = new Parser();
}

Compiler::~Compiler(){}

bool Compiler::PathIsRight()
{
    return std::filesystem::exists(
           std::filesystem::path(this->FilePathSource));
}

void Compiler::Run()
{
    if(!PathIsRight())
    {
        Console::PrintError("File cannot be founded! ("+this->FilePathSource+")");
        exit(EXIT_FAILURE);
    }

    std::string Line;
    FileReader.open(this->FilePathSource);

    if(FileReader.is_open() && FileReader.good())
    {
        while(std::getline(FileReader, Line))
        {
            ++LineCount;
            
            if(Line.empty() || 
               Line[0] == LANG::LINEBREAK ||
               Line[0] == LANG::LINECOMMENT && Line[1] == LANG::LINECOMMENT)
            {
                // # Do nothing
                // # this block is designed to catch and ignore lines in blank, tabs and other 
                // # throwaways elements 
            }
            else
            {
                this->Manager(Line);
            }
        }
    }

    FileReader.close();
}

void Compiler::Manager(std::string Line)
{
    Tokens_lst GetTokens = this->lexer->Tokenaze(Line);
    this->parser->RunCheck(GetTokens, this->LineCount);
}