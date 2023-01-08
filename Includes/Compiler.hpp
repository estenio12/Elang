// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <fstream>
#include <filesystem>

class Compiler
{
    private:
        std::string Path;
        std::ifstream FileReader;
        std::ofstream FileWriter;

    private:


    public:
        Compiler(char** Path);
        ~Compiler();

    private:
        bool PathIsRight();

    public:
        void Run();

};