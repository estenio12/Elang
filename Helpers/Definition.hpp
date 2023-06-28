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
#include "../Model/Ast.hpp"
#include "../Model/Token.hpp"

///@param string branch name 
///@param AstNode token list
///@example: string: variable-declaration:
///@example: AstNode: 'var' -> ':' -> <type> -> <identifier> -> ';' 
using AST = std::vector<std::pair<std::string, AstNode*>>;

namespace BRANCH_NAME
{
    const static std::string VARIABLE_DECLARATION = "VARIABLE_DECLARATION";
    const static std::string ARITHMETIC_OPERATION = "ARITHMETIC_OPERATION";
}

namespace STANDARD_SCOPE_NAME
{
    const static std::string GLOBALSCOPE = "GLOBALSCOPE";
}

namespace EXPECTED_TYPE
{
    const static std::string TUNDEFINED = "undefined";
    const static std::string TSTRING    = "string";
    const static std::string TNUMBER    = "number";
    const static std::string TBOOLEAN   = "boolean";
    const static std::string TCHARACTER = "character";
    const static std::string TVOID      = "void";
}

enum BRANCH_IDENTIFIER
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    ARITHMETIC_OPERATION
};

enum AST_DIRECTION
{
    LEFT,
    RIGHT
};