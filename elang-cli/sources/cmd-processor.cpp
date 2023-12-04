#include "../headers/cmd-processor.hpp"

CmdProcessor::CmdProcessor(std::vector<std::string> arguments):arguments(arguments){}

CmdProcessor::~CmdProcessor(){}

void CmdProcessor::Process()
{
   
    if(IsVersionCmd(arguments[0])) this->ExecuteVersion();

    if(IsHelpCmd(arguments[0])) this->ExecuteHelp();

    if(IsInitCmd(arguments[0])) 
    {
        if(arguments.size() <= 1)
        {
            Output::PrintError("Nome do projeto deve ser informado");
            Output::PrintCustomInfo("Exemplo: ", "elang --init meuprojeto");
            exit(EXIT_FAILURE);
        }

        this->ExecuteInit(arguments[1]);
    }
    
    // Output::PrintError("Comando não suportado");
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
    Output::Print("\n--init           iniciar um novo projeto.");
    Output::Print("\n--build          compilar projeto.");
}

void CmdProcessor::ExecuteInit(std::string project_name)
{
    try
    {
        auto project_config  = std::filesystem::path(project_name +"/"+project_name + ".elangproj");
        auto root_dir_name   = std::filesystem::path(project_name);
        auto dir_bin         = std::filesystem::path(project_name+"/bin");
        auto dir_build_files = std::filesystem::path(project_name+"/.buildfiles");

        if(std::filesystem::exists(project_config))
        {
            Output::PrintError("Já existe uma projeto com este nome neste diretório");
            exit(EXIT_FAILURE);
        }

        std::filesystem::create_directory(root_dir_name);
        std::filesystem::create_directories(dir_bin);
        std::filesystem::create_directories(dir_build_files);

        auto path_remove_config = std::filesystem::path(project_name +"/"+project_name + ".elangproj");
        auto path_remove_main   = std::filesystem::path(project_name +"/main.elang");

        if(std::filesystem::exists(path_remove_config))
            std::filesystem::remove(path_remove_config);

        if(std::filesystem::exists(path_remove_main))
            std::filesystem::remove(path_remove_main);

        std::fstream file(project_name +"/"+project_name + ".elangproj", std::ios::app);

        if(file.is_open() && file.good())
        {
            file << "projectName="+project_name+"\n";
            file << "buildTargetFile=main.elang\n";
            file << "outputBinary=bin\n";
        }

        file.close();

        std::fstream fileInit(project_name +"/main.elang", std::ios::app);

        if(fileInit.is_open() && fileInit.good())
        {
            fileInit << "# "+this->version+"\n";
            fileInit << "print(\"Hello world\\n\");\n";
        }

        fileInit.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string CmdProcessor::GetOSName()
{
    #ifdef _WIN32
        return "Windows 32-bit";
    #elif _WIN64
        return "Windows 64-bit";
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

#pragma endregion checkers


















