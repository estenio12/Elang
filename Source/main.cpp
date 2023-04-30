#include <iostream>

#include "../Include/Compiler.hpp"

int main(int argc, char** argv)
{
    auto compiler = new Compiler(argv[1]);

    compiler->Run();

    return EXIT_SUCCESS;
}