// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once 

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Parser
{   
    // # Sintax Variables
    private:
        Dictionary History;
        bool DeclaratorIsUp = false;
        int Level = 0;

    private:
        uint64_t LineCount = 0;

    public:
        Parser();
        ~Parser();
    
    private:
        void SetHistory(Dictionary );
        void RemoveHistory();
        void ExitProgram();
        void PrintError(std::string );

    public:
        void RunCheck(Tokens_lst, uint64_t );

    private:
        void SyntaxCheck(Dictionary );

    private:
        bool ValidateDeclarations(Dictionary );
        bool CheckDeclaration(Dictionary );
        bool CheckDeclarationDeclarator(Dictionary );
        bool CheckDeclarationIdentfier(Dictionary );
        bool CheckDeclarationTypeAssign(Dictionary );
        bool CheckDeclarationType(Dictionary );

};