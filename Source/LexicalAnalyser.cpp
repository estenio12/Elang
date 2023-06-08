#include "../Include/LexicalAnalyser.hpp"

Lexer::Lexer(std::string sourceCodePath)
{
    this->fileHandler.open(sourceCodePath, std::ios::binary);
}

Lexer::~Lexer(){}

token Lexer::GetNextToken()
{
    this->CheckTokenList();
    return this->currentTokenList[this->cursorTokenList];
}

token_list Lexer::Tokenize(std::string line)
{
    token_list list;
    std::string current_word;

    for(char letter : line)
    {
        if(this->IsNotAlphaNumeric(letter))
        {
            if(Checker::IsValidLine(current_word)) list.push_back(current_word);

            if(letter != DELIMITERS::WHITESPACE[0])
            {
                list.push_back(this->ConvertCharacterToToken(letter));
            }
            
            current_word.clear();
        }
        else
        {
            current_word.push_back(letter);
        }
    }

    return list;
}

token Lexer::ConvertCharacterToToken(char letter)
{
    token ntoken = "";
    ntoken.push_back(letter); 
    return ntoken; 
}

bool Lexer::IsNotAlphaNumeric(char letter)
{
    for(char iterator : ALPHA::ALPHANUMERIC)
    {
        if(letter == iterator)
        {
            return false;
        }
    }

    return true;
}

std::string Lexer::GetNextLineFromFile()
{
    std::string line;

    try
    {
        if(this->fileHandler)
        {
            if(std::getline(this->fileHandler, line))
            {
                return line;
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

    this->FileIsOpen = false;
    this->fileHandler.close();
    return "";
}

void Lexer::CheckTokenList()
{
    cursorTokenList++;

    if(cursorTokenList <= currentTokenList.size())
    {
        if(this->FileIsOpen)
        {
            auto getline = this->GetNextLineFromFile();
            getline = this->SanitizeLine(getline);
            this->lineCounter++;

            if(Checker::IsValidLine(getline))
            {
                currentTokenList = this->Tokenize(getline);
                cursorTokenList  = 0;
            }
            else
            {
                this->CheckTokenList();
            }
        }
        else
        {
            this->FileIsEnd = true;
        }
    }
}

std::string Lexer::SanitizeLine(std::string line)
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
               line[i] != DELIMITERS::BACKSPACE[0] &&
               line[i] != DELIMITERS::TABULATION[0])
            {
                nline.push_back(line[i]);
            }
       }
        
    }

    return nline;
}


