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

    private:
        bool ValidateMatch(std::vector<bool>);

    public:
        bool CheckVariableDeclaration(token_list );
        bool CheckValue(token_list );
        bool CheckCallFunction(token_list );
        bool CheckArgumentList(token_list );
        bool CheckJumpStatement(token_list );
        bool CheckCastExpression(token_list );
        bool CheckAdditiveExpression(token_list );
        bool CheckMultiplicativeExpression(token_list );
        bool CheckExpression(token_list );
        bool CheckLogicalExpression(token_list );
        bool CheckSystemCall(token_list );
        bool CheckParameterList(token_list );

    // # Value
    private:
        // bool ValueDigit(token_list );
        // bool ValueAlpha(token_list );
        // bool ValueIdentifier(token_list );
        // bool ValueCallFunction(token_list );
        // bool ValueExpression(token_list );
        // bool ValueChar(token_list );
        // bool ValueString(token_list );
        // bool ValueTrue(token_list );
        // bool ValueFalse(token_list );

    // # Variable Declaration
    private:
        bool VariableDeclarationOnlyDeclaration(token_list );
        // bool VariableDeclarationAssignValue(token_list );
        // bool VariableDeclarationAssignSystemCall(token_list );
        // bool VariableDeclarationAssignCastExpression(token_list );

    // # Call Function
    private:
        bool CallFunctionNoArgumentList(token_list );
        bool CallFunctionWithArgumentList(token_list );

    // # Argument List
    private:
        bool ArgumentListSingleValue(token_list );
        bool ArgumentListMultiValue(token_list );

    // # Additive Expression
    private:
        bool AdditiveExpression(token_list );

    // # Multiplicative Expression
    private:
        bool MultiplicativeExpression(token_list );

    // # Jump Statement
    private:
        bool JumpStatementReturn(token_list );
        bool JumpStatementBreak(token_list );
        bool JumpStatementContinue(token_list );

    // # Cast Expression
    private:
        bool CastExpression(token_list );

    // # Expression
    private:
        bool ExpressionAdditive(token_list );
        bool ExpressionMultiplicative(token_list );
        bool ExpressionOperation(token_list );
        bool ExpressionOperationScoped(token_list );

    // # Logical Expression
    private:
        bool LogicalExpression(token_list );

    // # System Call
    private:
        bool SystemCallWrite(token_list );
        bool SystemCallRead(token_list );

    // # Parameter List
    private:
        bool ParameterListSingleParamenter(token_list );
        bool ParameterListMultiParamenter(token_list );

};