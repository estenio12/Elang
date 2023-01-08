#include <iostream>

#include "../Includes/Compiler.hpp"
#include "../Includes/Console.hpp"

int main(int argc, char** argv)
{
    Compiler* CC = new Compiler(argv);
    CC->Run();

    delete CC;

    return EXIT_SUCCESS;
}