#include "../headers/cmd-processor.hpp"

CmdProcessor::CmdProcessor(std::vector<std::string> arguments):arguments(arguments){}

CmdProcessor::~CmdProcessor(){}

std::string CmdProcessor::Process()
{
    std::string OutputFileName = "MyApplication.cpp";

    if(IsVersionCmd(arguments[0])) 
        this->ExecuteVersion();
    else if(IsHelpCmd(arguments[0])) 
        this->ExecuteHelp();
    else 
    {
        if(arguments.size() > 1)
        {
            OutputFileName = arguments[1];
            if(!OutputFileName.ends_with(".cpp")) OutputFileName += ".cpp";
        }

        this->ExecuteBuild(arguments[0], OutputFileName);
    }

    return OutputFileName;
}

void CmdProcessor::ExecuteVersion()
{
    Output::PrintCustomSuccess("Version.: ", this->version);
    Output::PrintCustomSuccess("Author..: ", "Estenio Garcia");
    Output::PrintCustomSuccess("License.: ", "Apache 2.0");
    Output::PrintCustomSuccess("Platform: ", this->GetOSName());

    exit(EXIT_SUCCESS);
}

void CmdProcessor::ExecuteHelp()
{
    Output::Print("Uso: elang [opções] ...");
    Output::Print("Opções:");
    Output::Print("\n--version | --v  conferir a versão.");
    Output::Print("\n--help    | --h  ver os comandos disponíveis.");
    Output::Print("\n\nExemplo compilação de arquivo elang:");
    Output::Print("\n\nelang <meu-arquivo>.elang <nome do arquivo de saída>");
}

void CmdProcessor::ExecuteBuild(std::string source, std::string OutputFileName)
{
    try
    {
        auto compiler = new Compiler(source, OutputFileName);
        compiler->Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string CmdProcessor::GetOSName()
{
    #ifdef _WIN32
        return "Windows 32-bits";
    #elif _WIN64
        return "Windows 64-bits";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #elif __unix || __unix__
        return "Unix";
    #else
        return "Other";
    #endif
}

std::string CmdProcessor::ExtractDirectoryNameFromPath(std::string path)
{
    std::string buffer;
    std::string nbuffer;

    for(int i = path.size(); i > 0; i--)
    {
        if(path[i] != '/')
            buffer.push_back(path[i]);
        else
            break;
    }

    for(int i = buffer.size(); i > 0; i--)
        nbuffer.push_back(buffer[i]);

    return nbuffer;
}

std::vector<std::string> CmdProcessor::Split(std::string source, const char target)
{
    std::vector<std::string> vec;
    std::string buffer;

    for(auto letter : source)
    {
        if(letter == target)
        {
            vec.push_back(buffer);
            buffer.clear();
        }
        else
            buffer.push_back(letter);
    }

    vec.push_back(buffer);

    source.clear();
    buffer.clear();

    return vec;
}

#pragma region checkers

bool CmdProcessor::IsVersionCmd(std::string cmd)
{
    return cmd == "--version" || cmd == "version" ||
           cmd == "--v"       || cmd == "v";
}

bool CmdProcessor::IsHelpCmd(std::string cmd)
{
    return cmd == "--help" || cmd == "--h" || cmd == "-h" || cmd == "-help";
}

bool CmdProcessor::IsInitCmd(std::string cmd)
{
    return cmd == "--init" || cmd == "init";
}

bool CmdProcessor::IsBuildCmd(std::string cmd)
{
    return cmd == "build" || cmd == "--build" || cmd == "b" || cmd == "--b";
}

#pragma endregion checkers


















