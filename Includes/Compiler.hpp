// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Compiler
{
    private:
        std::string FilePathSource;
        std::string FilePathOutput;
        std::ifstream FileReader;
        std::ofstream FileWriter;

    private:
        uint64_t LineCount = 0;

    public:
        Compiler(char** Path);
        ~Compiler();

    private:
        bool PathIsRight();

    public:
        void Run();

};