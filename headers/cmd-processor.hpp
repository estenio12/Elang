// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

#include "../headers/output.hpp"
#include "../headers/compiler.hpp"

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
        std::string Process();

    // # CLI functions
    private:
        void ExecuteHelp();
        void ExecuteVersion();
        void ExecuteBuild(std::string source, std::string OutputFileName);

    private:
        bool IsVersionCmd(std::string cmd);
        bool IsHelpCmd(std::string cmd);
        bool IsInitCmd(std::string cmd);
        bool IsBuildCmd(std::string cmd);

    private:
        std::string GetOSName();
        std::string ExtractDirectoryNameFromPath(std::string path);
        std::vector<std::string> Split(std::string source, const char target);

};