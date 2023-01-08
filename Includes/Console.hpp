// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <iostream>

#if __linux
    #define SUCCESS_FLAG_MESSAGE "\033[32m"
    #define ERRO_FLAG_MESSAGE "\033[31m"
    #define WARNING_FLAG_MESSAGE "\033[33m"
    #define STANDARD_FLAG_MESSAGE "\033[39m"
#else
    #include <windows.h>
#endif

namespace Console
{
    static void PrintError(std::string Message )
    {
        #if __linux
            std::cerr << ERRO_FLAG_MESSAGE << "Error: ";
            std::cout << STANDARD_FLAG_MESSAGE << Message << std::endl; 
        #else

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            
            // # Write Message flag in red color
            SetConsoleTextAttribute(hConsole, 31);
            std::cerr << "Error: ";

            // # Write Message in white color
            SetConsoleTextAttribute(hConsole, 37);
            std::cout << Message << std::endl;

        #endif
    }

    static void PrintSuccess(std::string Message)
    {
        #if __linux
            std::cout << SUCCESS_FLAG_MESSAGE << "Error: ";
            std::cout << STANDARD_FLAG_MESSAGE << Message << std::endl; 
        #else

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            
            // # Write Message flag in red color
            SetConsoleTextAttribute(hConsole, 32);
            std::cout << "Success: ";

            // # Write Message in white color
            SetConsoleTextAttribute(hConsole, 37);
            std::cout << Message << std::endl;

        #endif
    }

    static void PrintWarning(std::string Message)
    {
        #if __linux
            std::cout << WARNING_FLAG_MESSAGE << "Error: ";
            std::cout << STANDARD_FLAG_MESSAGE << Message << std::endl; 
        #else

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            
            // # Write Message flag in red color
            SetConsoleTextAttribute(hConsole, 33);
            std::cout << "Warning: ";

            // # Write Message in white color
            SetConsoleTextAttribute(hConsole, 37);
            std::cout << Message << std::endl;

        #endif
    }
    
    static void Print(std::string Message)
    {
        #if __linux
            std::cout << STANDARD_FLAG_MESSAGE<< Message << std::endl; 
        #else

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            // # Write Message in white color
            SetConsoleTextAttribute(hConsole, 37);
            std::cout << Message << std::endl;

        #endif
    }
};