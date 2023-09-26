#include "../headers/parser.hpp"

EBRANCH_TYPE Parser::BindOperation(Token* token)
{
    if(IsVariableDeclaration(token)) return EBRANCH_TYPE::VARIABLE_DECLARATION;

    this->ThrowError(token, "Unexpected token");
    return EBRANCH_TYPE::UNDEFINED;
}

// # Checkers
bool Parser::IsVariableDeclaration(Token* token)
{
    if(token->value == KEYWORD::T_ARRAY ||
       token->value == KEYWORD::T_VAR   ||
       token->value == KEYWORD::T_CONST )
    {
        return true;
    }

    return false;
}

// # Builders
AstBranch* Parser::BuildVariableDeclaration(Token* token)
{
    auto variable = new VariableDeclaration();
    this->CheckMemoryAllocated<VariableDeclaration*>(variable);

    variable->isArray    = token->value == KEYWORD::T_ARRAY;
    variable->isConstant = token->value == KEYWORD::T_CONST;

    // # Free token from memory
    delete token;

    // # Get Identifier
    auto t_identifier = this->lexer->GetNextToken();

    if(t_identifier != nullptr)
    {
        if(t_identifier->type == TYPE_TOKEN::T_IDENTIDIER)
            variable->name = t_identifier->value;
        else
            this->ThrowError(t_identifier, "It's expected an idenifier");

        delete t_identifier;
    }

    // # Consume syntax ':'
    this->ExpectValue(DELIMITER::T_COLON, "It's expected the seperator '" +DELIMITER::T_COLON+ "'");

    // # Get Type
    auto t_type = this->lexer->GetNextToken();

    if(t_type != nullptr)
    {
        if(t_type->type == TYPE_TOKEN::T_TYPE)
            variable->type = t_type->value;
        else
            this->ThrowError(t_type, "It's expected an type after seperator.");
    }

    // # Get ';' or '='token
    auto t_bridge_token = this->lexer->GetNextToken();

    if(t_bridge_token == nullptr)
    {
        ThrowError(t_type, "Expected the ';' or '=' after type declaration");
    }
    else if(t_bridge_token->value == DELIMITER::T_ASSIGN)
    {
        variable->expression = BuildExpression();
    }
    else if(t_bridge_token->value == DELIMITER::T_EOF)
    {
        delete t_bridge_token;
    }
    else
    {
        ThrowError(t_type, "Expected the ';' or '=' after type declaration");
    }

    // # Free from memory
    delete t_type;

    auto branch = new AstBranch();
    branch->branch_variable_declaration = variable;
    branch->TYPE = EBRANCH_TYPE::VARIABLE_DECLARATION;

    return branch;
}






















