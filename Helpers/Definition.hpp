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
#include "../Include/Ast.hpp"

using token      = std::string;
using token_list = std::vector<token>;

///@param string branch name 
///@param AstNode token list
///@example: string: variable-declaration:
///@example: AstNode: 'var' -> ':' -> <type> -> <identifier> -> ';' 
using AST = std::vector<std::pair<std::string, AstNode*>>;

namespace BRANCH_IDENTIFIER
{
    static const std::string UNDEFINED            = "UNDEFINED";
    static const std::string VARIABLE_DECLARATION = "VARIABLE-DECLARATION";
}