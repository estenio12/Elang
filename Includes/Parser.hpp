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

    public:
        Parser();
        ~Parser();
    
    private:
        void RemoveHistory();
        void ExitProgram();

    public:
        void RunCheck(Tokens_lst );

    private:
        bool SintaxCheck(Dictionary );
        bool CheckEmptyHistory(Dictionary& );
        bool CheckDeclaratorHistory(Dictionary& );
        bool CheckDeclaratorTypeAssignmentHistory(Dictionary& );
        bool CheckDeclaratorTypeHistory(Dictionary& );
        bool CheckDeclaratorBranchHistory(Dictionary& );
        bool CheckDataAssignmentHistory(Dictionary& );
        bool CheckValueHistory(Dictionary& );
        bool CheckNumberHistory(Dictionary& );
        bool CheckIdentifierHistory(Dictionary& );

};