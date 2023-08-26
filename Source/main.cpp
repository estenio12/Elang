#include <iostream>
#include <chrono>
#include "../Include/Compiler.hpp"

std::string GetOSName();

int main(int argc, char** argv)
{
    // # Start Time capture
    auto start_time = std::chrono::high_resolution_clock::now();

    // # Delcaration & run
    auto compiler = new Compiler(argv[1]);
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

    #if __linux
        Output::PrintCustomSuccess("Output File Name: ", "app");
    #else 
        Output::PrintCustomSuccess("Output File Name: ", "app.exe");
    #endif

    Output::PrintCustomSuccess("Target Platform: ", GetOSName());
    Output::PrintCustomSuccess("Time Compilation: ", std::to_string(elapsed_seconds) + " seconds");

    return EXIT_SUCCESS;
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