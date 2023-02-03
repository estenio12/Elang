// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#pragma once

#include <string>

class AST_Node
{
    public:
        std::string Content;
        std::string LeftContent;
        AST_Node* RightContent;
        AST_Node* Parent;
        int PowerLevel = 0;
};

class ParseTree
{
    private:
        AST_Node* Root;
        int GlobalPowerLevel = 0;

    public:
        ParseTree();
        ~ParseTree();

    public:
        void CreateNode(std::string Content,
                        std::string LeftContent);
        void DeleteTree();

    private:
        void InsertNodeIntoTree(AST_Node* );
        void DeleteNodeChild(AST_Node* );
        AST_Node* GetLastNode(AST_Node* );
};