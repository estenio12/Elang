#include "../headers/parser.hpp"

BRANCH_TYPE Parser::BindOperation(Token* token)
{
    if(IsVariableDeclaration(token)) return BRANCH_TYPE::VARIABLE_DECLARATION;

    this->ThrowError(token, "Unexpected token");
    return BRANCH_TYPE::UNDEFINED;
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

        delete t_type;
    }

    // # Consume syntax ';'
    this->ExpectValue(DELIMITER::T_EOF, "Expected the ';' or '=' after type declaration");

    auto branch = new AstBranch();
    branch->branch_variable_declaration = variable;
    branch->TYPE = BRANCH_TYPE::VARIABLE_DECLARATION;

    return branch;
}





















