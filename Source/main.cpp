#include <iostream>
#include "../Include/Compiler.hpp"

int main(int argc, char** argv)
{
    // # Delcaration & run
    auto compiler = new Compiler(argv[1]);
    compiler->Run();

    // # Free 
    delete compiler;

    return EXIT_SUCCESS;
}