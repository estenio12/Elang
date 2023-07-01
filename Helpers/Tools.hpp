// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <string>
#include <iostream>
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Definition.hpp"
#include "../Include/Output.hpp"

class Tools
{
    public:
        Tools(){}
        ~Tools(){}

    public:
        bool Contains(std::string source, char target)
        {
            for(char letter : source) if(letter == target) return true;
            return false;
        }

        std::string TrimString(std::string source)
        {
            std::string nstring = "";

            for(char letter : source)
            {
                if(letter != ' ')
                {
                    nstring.push_back(letter);
                }
            }

            return nstring;
        }

        void PrintParseTree(AstNode* node, int deepCount = 0)
        {
            if(node != nullptr)
            {
                std::cout << "Debug ParseTree | Deep: " << deepCount << "\n";
                std::cout << "Debug ParseTree | Current Node: " << node->token->value << "\n";
                if(node->parent != nullptr)
                   std::cout << "Debug ParseTree | Parent: " << node->parent->token->value << "\n";
                else
                   std::cout << "Debug ParseTree | Parent: Null" << "\n";
                std::cout << "Debug ParseTree | Type: " << node->token->type << "\n";
                std::cout << "Debug ParseTree | hasNodeLeft: " << node->HasLeftNode() << "\n";
                std::cout << "Debug ParseTree | hasNodeRight: " << node->HasRightNode() << "\n\n";

                if(node->HasLeftNode())
                {
                    std::cout << "Debug ParseTree | Deep: " << deepCount << "\n";
                    std::cout << "Debug ParseTree | Current Node Left: " << node->left->token->value << "\n\n";
                }

                if(node->HasRightNode())
                {
                    this->PrintParseTree(node->right, ++deepCount);
                }
            }
        }
};
