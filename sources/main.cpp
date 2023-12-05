#include <iostream>
#include <string>
#include <chrono>

#include "../headers/compiler.hpp"
#include "../headers/output.hpp"
#include "../headers/cmd-processor.hpp"

std::vector<std::string> GetArguments(int argc, char** argv)
{
    std::vector<std::string> arguments;

    if(argc <= 1) 
    {
        Output::PrintError("Nenhum argumento informado."); 
        Output::PrintInfo("Digite elang --help para visualizar todos os comados disponíveis");
    }

    for(int i = 1; i < argc; i++)
        arguments.push_back(argv[i]);

    return arguments;
}

int main(int argc, char** argv)
{
    // # Start banchmark
    auto start = std::chrono::high_resolution_clock::now();

    auto processor = new CmdProcessor(GetArguments(argc, argv));
    auto fileName = processor->Process();

    // # Stop banchmark
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<float>(end - start);

    // # Close compilation
    Output::PrintSuccess("Compiled successfully");
    Output::PrintCustomInfo("Output file..: ", fileName);
    Output::PrintCustomInfo("Elapsed Time.: ", std::to_string(elapsed.count()));

    return EXIT_SUCCESS;
}