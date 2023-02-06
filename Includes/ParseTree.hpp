// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>
#include <vector>

#include "../Includes/Ast.hpp"
#include "../Helpers/SymbolTable.hpp""

class ParseTree
{
    private:
        std::vector<AST::AST_Node*> Tree;
        AST::AST_Node* Build;
        int GlobalPowerLevel = 0;

    public:
        ParseTree();
        ~ParseTree();

    public:
        void CreateNode(Dictionary );
        void Sort();

    private:
        void HandlerGlobalPowerLevel(std::string& );
        void Commit();
};