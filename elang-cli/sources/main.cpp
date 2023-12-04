#include <iostream>
#include <vector>

#include "../headers/output.hpp"
#include "../headers/cmd-processor.hpp"

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;

    if(argc <= 1) 
    {
        Output::PrintError("Nenhum argumento informado."); 
        Output::PrintInfo("Digite elang --help para visualizar todos os comados disponíveis");
    }

    for(int i = 1; i < argc; i++)
        arguments.push_back(argv[i]);

    auto processor = new CmdProcessor(arguments);

    processor->Process();

    return EXIT_SUCCESS;
}