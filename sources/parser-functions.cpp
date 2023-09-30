#include "../headers/parser.hpp"

EBRANCH_TYPE Parser::BindOperation(Token* token)
{
    if(IsVariableDeclaration(token)) return EBRANCH_TYPE::VARIABLE_DECLARATION;
    if(IsFunctionDeclaration(token)) return EBRANCH_TYPE::FUNCTION_DECLARATION;

    this->ThrowError(token, "Unexpected token");
    return EBRANCH_TYPE::UNDEFINED;
}

// # Checkers
bool Parser::IsVariableDeclaration(Token* token)
{
    if(token->value == KEYWORD::T_VAR   ||
       token->value == KEYWORD::T_CONST )
    {
        return true;
    }

    return false;
}

bool Parser::IsFunctionDeclaration(Token* token)
{
    if(token->value == KEYWORD::T_FUN) return true;
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

    this->InsertIdentifierIntoSymbolTable(branch);

    return branch;
}

AstBranch* Parser::BuildFunctionDeclaration(Token* token)
{
    auto function = new FunctionDeclaration();
    auto funModel = new FunctionIdenfierModel();

    // # KEYWORD 'fun' from memory
    delete token;

    this->CheckMemoryAllocated(function);

    auto t_fun_id = this->lexer->GetNextToken();

    if(t_fun_id != nullptr)
    {
        if(this->symbolTable->ExistsIdentifier(t_fun_id->value, this->currentScope, this->currentDeep) ||
           this->symbolTable->ExistsFunctionIdentifier(t_fun_id->value))
            ThrowError(t_fun_id, "duplicated identifier");

        funModel->name = t_fun_id->value;
    }
    else
        this->ThrowError(t_fun_id, "An identifier was expected after the keyword 'fun'");

    this->ExpectValue(DELIMITER::T_OPEN_PARAM, "Expected open parenthesis after identifier.");

    // # Read parameters
    while(true)
    {
        auto init_token = this->lexer->GetNextToken();

        if(init_token == nullptr)
        {
            Output::PrintError("Line: " + std::to_string(lexer->lineCounter) + " Unexpected the source code end");
            exit(EXIT_FAILURE);
        } 

        if(init_token->value == DELIMITER::T_CLOSE_PARAM) 
        {
            delete init_token;
            break;
        }

        // # expect keyword var
        this->ExpectValue(init_token, "Expected a keyword 'var' to parameter declaration");

        // # expect identifier
        auto id_token = this->lexer->GetNextToken();

        if(id_token->type == TYPE_TOKEN::T_IDENTIDIER)
        {
            this->ExpectValue(lexer->GetNextToken(), "Expect separator ':' after identifier ");

            // # Get type token
            auto type_token = this->lexer->GetNextToken();
        }
        else
            ThrowError(id_token, "expected identifier after declaration");
    }


    // # Insert into symbol table, now everybody know that function exists
    this->symbolTable->InsertFunctionIdentifier(funModel);

    // # Finishing
    auto branch = new AstBranch();
    branch->branch_function_declaration = function;
    branch->TYPE = EBRANCH_TYPE::FUNCTION_DECLARATION;

    return branch;
}




















