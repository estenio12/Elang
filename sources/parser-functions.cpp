#include "../headers/parser.hpp"

#pragma region CHECKERS

EBRANCH_TYPE Parser::BindOperation(Token* token)
{
    if(IsVariableDeclaration(token)) return EBRANCH_TYPE::VARIABLE_DECLARATION;
    if(IsFunctionDeclaration(token)) return EBRANCH_TYPE::FUNCTION_DECLARATION;
    if(IsReturnExpression(token)) return EBRANCH_TYPE::RETURN_EXPRESSION;
    if(IsAssignment(token)) return EBRANCH_TYPE::ASSIGNMENT;
    if(IsCallFunction(token)) return EBRANCH_TYPE::CALL_FUNCTION;
    if(IsWhileDeclaration(token)) return EBRANCH_TYPE::WHILE_DECLARATION;
    if(IsIfElseCondition(token)) return EBRANCH_TYPE::IF_ELSE_CONDITION;

    this->ThrowError(token, "Unexpected token");
    return EBRANCH_TYPE::UNDEFINED;
}

bool Parser::IsAssignment(Token* token)
{
    return this->symbolTable->ExistsIdentifier(token->value, this->currentScope, this->currentDeep);
}

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

bool Parser::IsWhileDeclaration(Token* token)
{
    return token->value == KEYWORD::T_WHILE;
}

bool Parser::IsIfElseCondition(Token* token)
{
    return token->value == KEYWORD::T_IF;
}

#pragma endregion

#pragma region BUILDERS

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
        {
            if(this->symbolTable->ExistsIdentifier(t_identifier->value, this->currentScope, this->currentDeep))
                this->ThrowError(t_identifier, "duplicating variable declaration");

            variable->name = t_identifier->value;
        }
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
        variable->expression = BuildExpression(this->CreateExpectedType(variable->type), nullptr);
    }
    else if(t_bridge_token->value == DELIMITER::T_EOF)
    {
        if(variable->isConstant)
            ThrowError(t_bridge_token, "constant variables must to be initialized");

        MemTools::FreeObjectFromMemory(t_bridge_token);
    }
    else
    {
        ThrowError(t_type, "Expected the ';' or '=' after type declaration");
    }

    // # Free from memory
    MemTools::FreeObjectFromMemory(t_type);

    auto branch = new AstBranch(variable, variable->IsGlobalScope());

    this->InsertIdentifierIntoSymbolTable(variable);

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
    this->ExpectValue(DELIMITER::T_OPEN_PAREM, "Expected open parenthesis after identifier.");

    // # Read parameters
    while(true)
    {
        // # Get parameters identifier
        auto id_token = this->GetNextToken("Expected a parameter identifier here");

        // # check type after closing parenthesis
        if(id_token->value == DELIMITER::T_CLOSE_PAREM) 
        {
            MemTools::FreeObjectFromMemory(id_token);

            this->ExpectValue(DELIMITER::T_COLON, "Expect a ':' after closing parenthesis");

            // # Get Type
            auto t_type = this->GetNextToken("It's expected an type after seperator.");

            if(t_type->type == TYPE_TOKEN::T_TYPE)
            {
                function->type = t_type->value;
                funModel->type = t_type->value;
            }
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
            param->type = type_token->value;

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

        if(next_token->value == DELIMITER::T_CLOSE_PAREM)
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

    // # Load body setting 
    auto policy = new BlockStmtPolicy();

    if(function->type != TYPE::T_VOID)
        policy->AddPolicy(BLOCK_STMT_POLICY::ALLOW_RETURN);

    // # Read Function Body
    function->block_stmt = this->BuildBlockStatement(policy, CreateExpectedType(function->type));

    // # Reset stats
    this->currentScope = GLOBAL_SCOPE;
    this->currentDeep  = GLOBAL_DEEP;

    // # Insert into symbol table, now everybody know that function exists
    this->symbolTable->InsertFunctionIdentifier(funModel);

    // # Complete Task
    auto branch = new AstBranch(function);
    return branch;
}

AstBranch* Parser::BuildReturnExpression(Token* token, std::vector<std::string> expected_type)
{
    auto return_expression = new ReturnExpression();

    // # Free from memory
    MemTools::FreeObjectFromMemory(token);

    return_expression->expression = BuildExpression(expected_type, nullptr);
    auto branch = new AstBranch(return_expression);
    return branch;
}

AstBranch* Parser::BuildCallFunction(Token* token, Tokens* tokenList)
{
    auto call_function = new CallFunction();
    auto fun_data = this->symbolTable->GetFunctionIdentifier(token->value);
    
    MemTools::FreeObjectFromMemory(token);

    // # build meta-data
    call_function->name = fun_data->name;
    call_function->type = fun_data->type;

    bool isTokenList = tokenList != nullptr;

    if(isTokenList)
        this->ExpectThisToken(tokenList->Shift(), DELIMITER::T_OPEN_PAREM, "Expected opening parenthesis");
    else
        this->ExpectValue(DELIMITER::T_OPEN_PAREM, "Expected opening parenthesis");

    // # Read arguments
    int argument_size = fun_data->parameterList.size();

    if(argument_size > 0)
    {
        auto argument_list = this->GetNewInstanceOfArgumentList(argument_size);
        int opened_paren   = 1;
        int argument_index = 0;

        // # Assign type to first index of argument list
        argument_list[argument_index]->expected_type = fun_data->GetTypeParameter(argument_index);

        // # Build argument list
        while(true)
        {
            Token* next_token = nullptr;

            if(isTokenList)
            {
                next_token = tokenList->Shift();

                std::string header = "Syntax Error (Line: "+std::to_string(this->lineHistory)+"): ";
                std::string msg    = "the source code ends abruptly before closing compilaion";
                
                if(next_token == nullptr) 
                {
                    Output::PrintCustomizeError(header, msg);
                    exit(EXIT_FAILURE);
                }

                this->lineHistory = token->line;
            }
            else
                next_token = this->GetNextToken("");

            if(next_token->value == DELIMITER::T_COMMA)
            {
                argument_index++;

                if(argument_size == 1 || argument_index > argument_size - 1)
                    this->ThrowError(next_token, "Too many arguments passed o function '" + fun_data->name + "'. This function expect " + std::to_string(fun_data->parameterList.size()) + " arguments");

                argument_list[argument_index]->expected_type = fun_data->GetTypeParameter(argument_index);
                continue;
            }

            if(next_token->value == DELIMITER::T_OPEN_PAREM)   
            {
                opened_paren++;
                argument_list[argument_index]->AddToken(next_token);
                continue;
            }

            if(next_token->value == DELIMITER::T_CLOSE_PAREM)
            {
                opened_paren--;

                if(opened_paren == 0)
                    break;
                else if(opened_paren < 0)
                    this->ThrowError(next_token, "Unexpected closing parenthesis");
            }

            argument_list[argument_index]->AddToken(next_token);
        }

        // # Build expression
        for(auto item : argument_list)
        {
            // # Check if all argument has filled
            if(item->GetSize() == 0)
            {
                // # standard messages
                std::string few_arg_header_msg = "Syntax error (Line: "+std::to_string(lineHistory)+"): "; 
                std::string few_arg_error_msg  = "Too few arguments to function '" + fun_data->name + "'. This function expect " + std::to_string(fun_data->parameterList.size()) + " arguments";
                Output::PrintCustomizeError(few_arg_header_msg, few_arg_error_msg);
                exit(EXIT_FAILURE);
            }

            auto expression = this->BuildExpression(this->CreateExpectedType(item->expected_type), item);
            call_function->InsertArgument(expression);
        }
    }
    else
    {
        if(isTokenList)
            this->ExpectThisToken(tokenList->Shift(), DELIMITER::T_CLOSE_PAREM, "Expect closing parenthesis.");
        else
            this->ExpectValue(DELIMITER::T_CLOSE_PAREM, "Expect closing parenthesis.");
    }

    // # Build branch
    auto branch = new AstBranch(call_function);
    return branch;
}

AstBranch* Parser::BuildAssignment(Token* token)
{
    auto assignment = new Assignment();
    auto variable = this->symbolTable->GetIdentifier(token->value, this->currentScope, this->currentDeep);

    if(variable->IsConstant)
        this->ThrowError(token, "Cannot assign value to constant identifier");

    MemTools::FreeObjectFromMemory(token);

    assignment->name = variable->name;
    
    this->ExpectValue(DELIMITER::T_ASSIGN, "Expected '=' after the identifier to attribution value.");

    assignment->expression = this->BuildExpression(this->CreateExpectedType(variable->type), nullptr);

    return new AstBranch(assignment);
}

AstBranch* Parser::BuildBreakStatement(Token* token)
{
    if(token->value != KEYWORD::T_BREAK) this->ThrowError(token, "Unexpected token");
    this->ExpectValue(DELIMITER::T_EOF, "Expected ';' after keyword break");
    
    return new AstBranch(new BreakStatement());
}

AstBranch* Parser::BuildWhileDeclaration(BlockStmtPolicy* policy, Token* token, std::vector<std::string> expected_type)
{
    auto while_declaration = new WhileDeclaration();
    
    MemTools::FreeObjectFromMemory(token);

    this->ExpectValue(DELIMITER::T_OPEN_PAREM, "Expected opening parenthesis");

    // # Read arguments
    auto allow_types = this->CreateExpectedType(TYPE::T_INT);
    allow_types.push_back(TYPE::T_BOOL);

    int opened_paren = 1;
    auto tokens = new Tokens();

    while(true)
    {
        auto next_token = this->GetNextToken("");

        if(next_token->value == DELIMITER::T_OPEN_PAREM)   
        {
            opened_paren++;
            tokens->AddToken(next_token);
            continue;
        }

        if(next_token->value == DELIMITER::T_CLOSE_PAREM)
        {
            opened_paren--;

            if(opened_paren == 0)
                break;
            else if(opened_paren < 0)
                this->ThrowError(next_token, "Unexpected closing parenthesis");
        }

        tokens->AddToken(next_token);
    }

    while_declaration->condition = this->BuildExpression(allow_types, tokens);

    // # Read Body
    policy->AddPolicy(BLOCK_STMT_POLICY::ALLOW_BREAK);
    while_declaration->block_stmt = this->BuildBlockStatement(policy, expected_type);

    // # Build branch
    auto branch = new AstBranch(while_declaration);
    return branch;
}

AstBranch* Parser::BuildIfElseCondition(BlockStmtPolicy* policy, Token* token, std::vector<std::string> expected_type)
{
    auto if_else_condition = new IfElseCondition();
    
    MemTools::FreeObjectFromMemory(token);

    this->ExpectValue(DELIMITER::T_OPEN_PAREM, "Expected opening parenthesis");

    // # Read arguments
    auto allow_types = this->CreateExpectedType(TYPE::T_INT);
    allow_types.push_back(TYPE::T_BOOL);

    int opened_paren = 1;
    auto tokens = new Tokens();

    while(true)
    {
        auto next_token = this->GetNextToken("");

        if(next_token->value == DELIMITER::T_OPEN_PAREM)   
        {
            opened_paren++;
            tokens->AddToken(next_token);
            continue;
        }

        if(next_token->value == DELIMITER::T_CLOSE_PAREM)
        {
            opened_paren--;

            if(opened_paren == 0)
                break;
            else if(opened_paren < 0)
                this->ThrowError(next_token, "Unexpected closing parenthesis");
        }

        tokens->AddToken(next_token);
    }

    if_else_condition->condition = this->BuildExpression(allow_types, tokens);

    // # Read if block statement
    policy->AddPolicy(BLOCK_STMT_POLICY::ALLOW_ELSE_CONDITION);
    if_else_condition->if_block_stmt = this->BuildBlockStatement(policy, expected_type);

    if(if_else_condition->if_block_stmt->closeWithElse)
    {
        policy->RemovePolicy(BLOCK_STMT_POLICY::ALLOW_ELSE_CONDITION);
        if_else_condition->else_block_stmt = this->BuildBlockStatement(policy, expected_type);
    }

    // # Build branch
    auto branch = new AstBranch(if_else_condition);
    return branch;
}

#pragma endregion














