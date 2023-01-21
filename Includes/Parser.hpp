// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#ifndef PARSER_H
#define PARSER_H

#include <cstdint>

#include "../Includes/Console.hpp"
#include "../Helpers/SymbolTable.hpp"

class Parser
{   
    // # Sintax Variables
    private:
        Dictionary History;
        bool DeclaratorIsUp = false;
        int Level = 0;
        int ParanOpen = 0;

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
        void CloseDeclaration();
        void CallbackLevel();
        void AddParanOpen();
        void RemoveParanOpen();
        void CheckParentheses();

    public:
        void RunCheck(Tokens_lst, uint64_t );

    private:
        void SyntaxCheck(Dictionary );

    private:
        bool ValidateDeclarations(Dictionary& );
        bool CheckDeclaration(Dictionary );
        bool CheckDeclarationDeclarator(Dictionary );
        bool CheckDeclarationIdentfier(Dictionary );
        bool CheckDeclarationTypeAssign(Dictionary );
        bool CheckDeclarationType(Dictionary );
        
        bool CheckOperation(Dictionary );

};

#endif