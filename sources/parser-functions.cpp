#include "../headers/parser.hpp"

EBRANCH_TYPE Parser::BindOperation(Token* token)
{
    if(IsVariableDeclaration(token)) return EBRANCH_TYPE::VARIABLE_DECLARATION;
    if(IsFunctionDeclaration(token)) return EBRANCH_TYPE::FUNCTION_DECLARATION;
    if(IsReturnExpression(token)) return EBRANCH_TYPE::RETURN_EXPRESSION;
    if(IsCallFunction(token)) return EBRANCH_TYPE::CALL_FUNCTION;

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

bool Parser::IsReturnExpression(Token* token)
{
    if(token->value == KEYWORD::T_RETURN) return true;
    return false;
}

bool Parser::IsCallFunction(Token* token)
{
    return this->symbolTable->ExistsFunctionIdentifier(token->value);
}

// # Builders
AstBranch* Parser::BuildVariableDeclaration(Token* token)
{
    auto variable = new VariableDeclaration();

    this->CheckMemoryAllocated<VariableDeclaration*>(variable);

    variable->deep       = this->currentDeep;
    variable->scopeName  = this->currentScope;
    variable->isArray    = token->value == KEYWORD::T_ARRAY;
    variable->isConstant = token->value == KEYWORD::T_CONST;

    // # Free token from memory
    MemTools::FreeObjectFromMemory(token);

    // # Get Identifier
    auto t_identifier = this->GetNextToken("It's expected an identifier");

    if(t_identifier != nullptr)
    {
        if(t_identifier->type == TYPE_TOKEN::T_IDENTIDIER)
            variable->name = t_identifier->value;
        else
            this->ThrowError(t_identifier, "It's expected an identifier");

        MemTools::FreeObjectFromMemory(t_identifier);
    }

    // # Consume syntax ':'
    this->ExpectValue(DELIMITER::T_COLON, "It's expected the '" +DELIMITER::T_COLON+ "' after identifier");

    // # Get Type
    auto t_type = this->GetNextToken("It's expected an type after seperator.");

    if(t_type != nullptr)
    {
        if(t_type->type == TYPE_TOKEN::T_TYPE)
            variable->type = t_type->value;
        else
            this->ThrowError(t_type, "It's expected an type after seperator.");
    }

    // # Get ';' or '='token
    auto t_bridge_token = this->GetNextToken("Expected the ';' or '=' after type declaration");

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
        MemTools::FreeObjectFromMemory(t_bridge_token);
    }
    else
    {
        ThrowError(t_type, "Expected the ';' or '=' after type declaration");
    }

    // # Free from memory
    MemTools::FreeObjectFromMemory(t_type);

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

    this->CheckMemoryAllocated(function);
    this->CheckMemoryAllocated(funModel);

    // # Set states
    this->currentScope = function->name;
    this->currentDeep++;
    int endStatmetCount = 1;

    // # KEYWORD 'fun' from memory
    MemTools::FreeObjectFromMemory(token);

    // # Function identifier validations
    auto t_fun_id = this->GetNextToken("An identifier was expected after the keyword 'fun'");

    if(this->symbolTable->ExistsIdentifier(t_fun_id->value, this->currentScope, this->currentDeep) ||
       this->symbolTable->ExistsFunctionIdentifier(t_fun_id->value) &&
       this->symbolTable->GetFunctionIdentifier(t_fun_id->value)->IsDeclared == true)
        ThrowError(t_fun_id, "duplicated identifier");

    funModel->name = t_fun_id->value;
    function->name = t_fun_id->value;

    MemTools::FreeObjectFromMemory(t_fun_id);

    // # Consume opening parenthesis 
    this->ExpectValue(DELIMITER::T_OPEN_PARAM, "Expected open parenthesis after identifier.");

    // # Read parameters
    while(true)
    {
        // # Get parameters identifier
        auto id_token = this->GetNextToken("Expected a parameter identifier here");

        // # check type after closing parenthesis
        if(id_token->value == DELIMITER::T_CLOSE_PARAM) 
        {
            MemTools::FreeObjectFromMemory(id_token);

            this->ExpectValue(DELIMITER::T_COLON, "Expect a ':' after closing parenthesis");

            // # Get Type
            auto t_type = this->GetNextToken("It's expected an type after seperator.");

            if(t_type->type == TYPE_TOKEN::T_TYPE)
                function->type = t_type->value;
            else
                this->ThrowError(t_type, "It's expected an function return type here");

            MemTools::FreeObjectFromMemory(t_type);
            break;
        }
        else if(id_token->type == TYPE_TOKEN::T_IDENTIDIER)
        {
            // # consume ':'
            this->ExpectValue(DELIMITER::T_COLON, "Expect separator ':' after identifier ");

            // # Get type
            auto type_token = this->GetNextToken("It's expected an type after seperator.");

            if(type_token->type != TYPE_TOKEN::T_TYPE)
                this->ThrowError(type_token, "It's expected an type after seperator.");

            auto param = new ParameterDeclaration();
            param->name = id_token->value;
            param->type = type_token->type;

            funModel->parameterList.push_back(param);
            function->parameterList.push_back(param);

            // # Insert into symbol table
            auto id_model = new IdentifierModel
            (
                id_token->value,
                type_token->value,
                this->currentScope,
                this->currentDeep
            );

            this->symbolTable->InsertIdentifier(id_model);

            // # Free tokens from memory
            MemTools::FreeObjectFromMemory(id_token);
            MemTools::FreeObjectFromMemory(type_token);
        }
        else
            ThrowError(id_token, "Unexpected token here");

        // # Check if next token is comma or close parentheses
        auto next_token = this->GetNextToken("Expect ',' or ')' after parameter declaration");

        if(next_token->value == DELIMITER::T_CLOSE_PARAM)
        {
            MemTools::FreeObjectFromMemory(next_token);

            this->ExpectValue(DELIMITER::T_COLON, "Expect separate after close parentheses");

            // # Get Type
            auto t_type = this->GetNextToken("It's expected an type after seperator.");

            if(t_type->type != TYPE_TOKEN::T_TYPE)
                this->ThrowError(t_type, "It's expected an type after seperator.");

            function->type = t_type->value;
            funModel->type = t_type->value;

            MemTools::FreeObjectFromMemory(t_type);
            break;
        }
        else if(next_token->value == DELIMITER::T_COMMA)
            continue;
        else
            this->ThrowError(next_token, "Expect ',' or ')' after parameter declaration");
    }

    // # Read Function Body
    while(endStatmetCount > 0)
    {
        auto stmt_token = this->GetNextToken("Expected 'end' keyword to close function statement");

        if(stmt_token->value == KEYWORD::T_END) 
        {
            MemTools::FreeObjectFromMemory(stmt_token);
            endStatmetCount--;
            continue;
        }

        auto operation = this->BindOperation(stmt_token);

        switch(operation)
        {
            case EBRANCH_TYPE::VARIABLE_DECLARATION:
                function->listBodyLocalVariableDeclaration.push_back(BuildVariableDeclaration(stmt_token)->branch_variable_declaration);
            break;

            case EBRANCH_TYPE::RETURN_EXPRESSION:
                function->listBodyLocalReturnExpression.push_back(BuildReturnExpression(stmt_token));
            break;

            case EBRANCH_TYPE::CALL_FUNCTION:
                function->listBodyLocalCallFunction.push_back(BuildCallFunction(token)->branch_call_function_declaration);
                this->ExpectValue(DELIMITER::T_EOF, "Expected ';' after the called function ");
            break;

            default:
                ThrowError(stmt_token, "Unexpected token ");
            break;
        }
    }

    // # Reset stats
    this->currentScope = GLOBAL_SCOPE;
    this->currentDeep  = GLOBAL_DEEP;

    // # Insert into symbol table, now everybody know that function exists
    this->symbolTable->InsertFunctionIdentifier(funModel);

    // # Complete Task
    auto branch = new AstBranch();
    branch->branch_function_declaration = function;
    branch->TYPE = EBRANCH_TYPE::FUNCTION_DECLARATION;

    return branch;
}

ReturnExpression* Parser::BuildReturnExpression(Token* token)
{
    auto return_expression = new ReturnExpression();

    // # Free from memory
    MemTools::FreeObjectFromMemory(token);

    return_expression->expression = BuildExpression();

    return return_expression;
}

AstBranch* Parser::BuildCallFunction(Token* token)
{
    auto call_function = new CallFunction();
    auto fun_data = this->symbolTable->GetFunctionIdentifier(token->value);
    
    MemTools::FreeObjectFromMemory(token);

    // # build meta-data
    call_function->name = fun_data->name;
    call_function->type = fun_data->type;

    this->ExpectValue(DELIMITER::T_OPEN_PARAM, "Expected opening parenthesis");

    // # build argument list
    int param_readed = fun_data->parameterList.size();

    if(param_readed > 0)
    {
        while(param_readed > 0)
        {
            auto expr = BuildExpression();            
            call_function->InsertArgument(expr);
            param_readed--;

            if(expr->TerminateWithCloseParenthesis && param_readed > 0)
            {
                Output::PrintCustomizeError("Syntax error (Line: "+std::to_string(lineHistory)+"): ", "Too few arguments to function '" + fun_data->name + "'. This function expect " + std::to_string(fun_data->parameterList.size()) + " arguments");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        this->ExpectValue(DELIMITER::T_CLOSE_PARAM, "Expect closing parenthesis.");

    // # Build branch
    auto branch = new AstBranch();
    branch->branch_call_function_declaration = call_function;
    branch->TYPE = EBRANCH_TYPE::CALL_FUNCTION;
    return branch;
}
















