#include <iostream>
#include <filesystem>
#include "Output.hpp"

const std::string APP_NAME = "MyApplication";

bool IsLinuxOS();
std::string GetOSName();
bool CheckFileExists(std::string path);
void CompileForLinux();
void CompileForWindows();

int main(int argc, char** argv)
{
    // # Start Time capture
    auto start_time = std::chrono::high_resolution_clock::now();

    bool IsLinux = IsLinuxOS();

    std::string path = argv[1];
    if(!CheckFileExists(path))
       Output::PrintCustomizeError("Fatal error: ", path + " cannot be found!");

    // # EXECUTE ELANG COMPILER
    std::string COMPILER_COMMAND = "./tools/elc " + path;
    system(COMPILER_COMMAND.c_str());

    // # EXECUTE C++ COMPILER
    if(IsLinux)
       CompileForLinux();
    else
       CompileForWindows();

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

    return EXIT_SUCCESS;
}

bool IsLinuxOS()
{
    #if __linux
        return true;
    #else
        return false;
    #endif
}

bool CheckFileExists(std::string path)
{   
    return std::filesystem::exists(std::filesystem::path(path));
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

void CompileForLinux()
{
    std::string CPP_COMPILER_COMMAND = "g++ app.cpp -std=c++17 -o " + APP_NAME;
    std::string CPP_DELETE_FILE = "rm -r app.cpp";
    system(CPP_COMPILER_COMMAND.c_str());
    system(CPP_DELETE_FILE.c_str());
}

void CompileForWindows()
{
    std::string CPP_COMPILER_COMMAND = "g++ app.cpp -std=c++17 -o app";
    std::string CPP_DELETE_FILE = "rm -r app.cpp";
    system(CPP_COMPILER_COMMAND.c_str());
    system(CPP_DELETE_FILE.c_str());
}


