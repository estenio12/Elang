#include "../Includes/Compiler.hpp"

Compiler::Compiler(char** Path)
{
    this->FilePathSource = Path[1];
    this->FilePathOutput = "./Test/App.html";
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
               Line[0] == DEFAULT::LINEBREAK ||
               Line[0] == DEFAULT::LINECOMMENT && Line[1] == DEFAULT::LINECOMMENT)
            {
                // # Do nothing
            }
            else
            {
                Console::Print(Line);
            }
        }
    }

    FileReader.close();
}