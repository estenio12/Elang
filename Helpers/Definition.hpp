// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
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
    const static std::string VARIABLE_DECLARATION  = "VARIABLE_DECLARATION";
    const static std::string EXPRESSION            = "EXPRESSION";
    const static std::string FUNCTION_DECLARATION  = "FUNCTION_DECLARATION";
    const static std::string END_STATEMENT         = "END_STATEMENT";
    const static std::string RETURN_EXPRESSION     = "RETURN_EXPRESSION";
    const static std::string ASSIGNMENT_EXPRESSION = "ASSIGNMENT_EXPRESSION";
    const static std::string CALL_FUNCTION         = "CALL_FUNCTION";
    const static std::string CONDITION_DECLARATION = "CONDITION_DECLARATION";
    const static std::string CLOSE_STATEMENT       = "CLOSE_STATEMENT";
    const static std::string IO_SYSTEM             = "IO_SYSTEM";
    const static std::string CASTING               = "CASTING";
}

namespace STANDARD_SCOPE_NAME
{
    const static std::string GLOBALSCOPE = "GLOBALSCOPE";
}

namespace EXPECTED_TYPE
{
    const static std::string TUNDEFINED = "undefined";
    const static std::string TTEXT      = "text";
    const static std::string TNUMBER    = "number";
    const static std::string TBOOLEAN   = "boolean";
    const static std::string TCHARACTER = "char";
    const static std::string TVOID      = "void";
}

enum BRANCH_IDENTIFIER
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION,
    FUNCTION_DECLARATION,
    BUILD_PARAMETER_LIST,
    STATEMENT,
    RETURN_EXPRESSION,
    ASSIGNMENT,
    CALL_FUNCTION,
    CONDITION_DECLARATION,
    CLOSE_STATEMENT,
    FOR_STATEMENT
};

enum AST_DIRECTION
{
    LEFT,
    RIGHT
};

enum TYPE_ID
{
    _VARIABLE_ASSIGNMENT,
    _CALL_FUNCTION,
    _IO_SYSTEM,
    _CASTING,
    _NONE
};

