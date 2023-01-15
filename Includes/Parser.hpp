#pragma once 

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Parser
{   
    private:
        Dictionary History;
        bool DeclaratorIsUp = false;
        int Level = 0;

    public:
        Parser();
        ~Parser();
    
    private:
        void AddHistory(std::string, std::string );
        void RemoveHistory();
        void ExitProgram();

    public:
        void RunCheck(Tokens_lst );

    private:
        bool SintaxCheck(Dictionary );
        bool CheckEmptyHistory(Dictionary& );

};