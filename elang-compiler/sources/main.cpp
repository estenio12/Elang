#include <iostream>

#include "../headers/compiler.hpp"

int main(int argc, char** argv)
{
    auto compiler = new Compiler(argv[1], argv[2]);
    compiler->Run();

    return EXIT_SUCCESS;
}