// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: MIT
// ## 
// #######################################

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Helpers/Definition.hpp"
#include "../Helpers/SymbolTable.hpp"
#include "../Helpers/Tools.hpp"

class SyntaxPatternMatch
{
    public:
        SyntaxPatternMatch();
        ~SyntaxPatternMatch();

    public:
        bool MatchVariableDeclaration(token_list );
    
    private:
        bool ValidateMatch(std::vector<bool>);

    private:
        bool VariableDeclarationOnlyDeclaration(token_list );
        // bool VariableDeclarationAssignValue(token_list );
        // bool VariableDeclarationAssignSystemCall(token_list );
        // bool VariableDeclarationAssignCastExpression(token_list );

};