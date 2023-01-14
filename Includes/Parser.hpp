#pragma once 

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Parser
{   
    private:
        Dictionary History;
        bool DeclaratorIsUp = false;

    public:
        Parser();
        ~Parser();
    
    private:
        void AddHistory(std::string, std::string );
        void RemoveHistory();

    public:
        void RunCheck(Tokens_lst );

    private:
        bool SintaxCheck(std::string );


};