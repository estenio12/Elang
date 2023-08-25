#include <iostream>
#include <chrono>
#include "../Include/Compiler.hpp"

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
    Output::PrintCustomSuccess("Time Compilation: ", std::to_string(elapsed_seconds) + " seconds");

    return EXIT_SUCCESS;
}