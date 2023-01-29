// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#ifndef PARSER_H
#define PARSER_H

#include <cstdint>

#include "../Includes/Console.hpp"
#include "../Includes/TableIdentifier.hpp"
#include "../Helpers/SymbolTable.hpp"

class Parser
{   
    // # Sintax Variables
    private:
        Dictionary History;
        bool DeclaratorIsUp = false;
        bool DeclaratorItsAssigned = false;
        int Level = 0;
        int ParanOpen = 0;

    // # Semantic Variables
    private:
        Dictionary SemanticHistory;
        bool SemanticDeclaratorIsUp = false;
        bool SemanticDeclaratorIsAssigned = false;
        int SemanticLevel = 0;
        int SemanticParanOpen = 0;
        bool ItsConstant = false;
        std::string CurrentIdentifier = "";

    private:
        uint64_t LineCount = 0;
        TableID* IDTable;

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
        void SetSemanticHistory(Dictionary );
        void RemoveSemanticHistory();
        void SetCurrentIdentifier(std::string );
        void RemoveCurrentIdentifier();
        void SemanticCloseDeclaration();

    public:
        void RunCheck(Tokens_lst, uint64_t );

    private:
        void SyntaxCheck(Dictionary );
        void SemanticCheck(Dictionary );

    // # Syntax
    private:
        bool SyntaxValidateDeclarations(Dictionary& );
        bool SyntaxCheckDeclaration(Dictionary );
        bool SyntaxCheckDeclarationDeclarator(Dictionary );
        bool SyntaxCheckDeclarationIdentfier(Dictionary );
        bool SyntaxCheckDeclarationTypeAssign(Dictionary );
        bool SyntaxCheckDeclarationType(Dictionary );
        bool SyntaxCheckOperation(Dictionary );

    // # Semantic
    private:
        bool SemanticValidateDeclarations(Dictionary& );
        bool SemanticCheckDeclaration(Dictionary );
        bool SemanticCheckDeclarationDeclarator(Dictionary );
        bool SemanticCheckDeclarationIdentfier(Dictionary );
        bool SemanticCheckDeclarationTypeAssign(Dictionary );
        bool SemanticCheckDeclarationType(Dictionary );
        bool SemanticCheckOperation(Dictionary );
};

#endif