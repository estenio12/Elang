#include <iostream>
#include <chrono>
#include "../Include/Compiler.hpp"

const std::string APP_NAME = "MyApplication";

bool IsLinuxOS();
void PrintVersion();
std::string GetOSName();
void ExecuteCompilation(std::string);

int main(int argc, char** argv)
{
    std::string CMD = argv[1];

    if(CMD == "--version" || CMD == "--v" || CMD == "-v" || CMD == "-version" )
       PrintVersion();
    else
       ExecuteCompilation(CMD);

    return EXIT_SUCCESS;
}

void PrintVersion()
{
    Output::PrintCustomSuccess("Version: ", "(C) Elang compiler v1.0");
    Output::PrintCustomSuccess("License: ", "Apache 2.0");
    Output::PrintCustomSuccess("Author: ", "Estenio Garcia");
}

void ExecuteCompilation(std::string argv)
{
    // # Start Time capture
    auto start_time = std::chrono::high_resolution_clock::now();

    bool IsLinux = IsLinuxOS();
    std::string path = argv;

    // # Delcaration & run
    auto compiler = new Compiler(path);
    compiler->Run();

    // # Free 
    delete compiler;

    // # End Time Capture
    auto end_time = std::chrono::high_resolution_clock::now();

    // # Calculate time diff
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // # Get final result
    double elapsed_seconds = duration.count() / 1000000.0;

    Output::PrintSuccess("Compile finished!");

    if(IsLinux)
        Output::PrintCustomSuccess("Output File Name: ", APP_NAME);
    else 
        Output::PrintCustomSuccess("Output File Name: ", APP_NAME + ".exe");

    Output::PrintCustomSuccess("Target Platform: ", GetOSName());
    Output::PrintCustomSuccess("Time Compilation: ", std::to_string(elapsed_seconds) + " seconds");
}

std::string GetOSName()
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

bool IsLinuxOS()
{
    #if __linux
        return true;
    #else
        return false;
    #endif
}
