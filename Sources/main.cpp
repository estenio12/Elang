#include <iostream>

#include "../Includes/Console.hpp"

int main()
{
    
    Console::PrintError("Teste erro");
    Console::PrintSuccess("Teste success");
    Console::PrintWarning("Teste warning");
    Console::PrintStandard("Teste Standard");

    return EXIT_SUCCESS;
}