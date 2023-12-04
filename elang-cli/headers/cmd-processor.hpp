// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include "../headers/output.hpp"

class CmdProcessor
{
    private:
        std::vector<std::string> arguments;

    private:
        std::string version = "Elang v1.0";

    public:
        CmdProcessor(std::vector<std::string> arguments);
        ~CmdProcessor();

    public:
        void Process();

    // # CLI functions
    private:
        void ExecuteHelp();
        void ExecuteVersion();
        void ExecuteInit(std::string project_name);
        // void ExecuteCompiler();

    private:
        bool IsVersionCmd(std::string cmd);
        bool IsHelpCmd(std::string cmd);
        bool IsInitCmd(std::string cmd);

    private:
        std::string GetOSName();

};