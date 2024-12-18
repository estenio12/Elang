#include "../headers/parser.hpp"

Parser::Parser(Lexer* lexer, SymbolTable* symbolTable, Ast* ast):lexer(lexer), symbolTable(symbolTable), ast(ast)
{
    this->LoadElangLibrary();
}

Parser::~Parser(){}

Ast* Parser::Parse()
{
    // # Passing
    while(true)
    {
        // # Busca próximo token.,
        auto token = this->lexer->GetNextToken();

        // # Verifica se é nulo, caso verdadeiro, a fase análise sintática acabou.
        if(token == nullptr) break;

        // # Identifica qual operação está sendo feita.
        auto operation = this->BindOperation(token);

        switch(operation)
        {
            case EBRANCH_TYPE::VARIABLE_DECLARATION:
                PushToAst(this->BuildVariableDeclaration(token));
            break;

            case EBRANCH_TYPE::FUNCTION_DECLARATION:
                PushToAst(this->BuildFunctionDeclaration(token));
            break;

            case EBRANCH_TYPE::CALL_FUNCTION:
                PushToAst(this->BuildCallFunction(token));
                this->ExpectValue(DELIMITER::T_EOF, "Expected ';' after the called function ");
            break;

            case EBRANCH_TYPE::ASSIGNMENT:
                PushToAst(this->BuildAssignment(token));
            break;

            case EBRANCH_TYPE::WHILE_DECLARATION:
                PushToAst(this->BuildWhileDeclaration(new BlockStmtPolicy(), token, this->CreateExpectedType("")));
            break;

            case EBRANCH_TYPE::IF_ELSE_CONDITION:
                PushToAst(this->BuildIfElseCondition(new BlockStmtPolicy(), token, this->CreateExpectedType("")));
            break;
            
            default:
                ThrowInternalError("Parser operation not implemented!");
            break;
        }
    }

    // # Return Ast
    return this->ast;
}

void Parser::ThrowError(Token* token, std::string message)
{
    std::string lineError = "Line: " + std::to_string(token->line) + ", Col: " + std::to_string(token->startpos);
    Output::PrintCustomizeError("Syntax Error (" + lineError + "): ", message + " | Last token found '" + token->value + "'");
    MemTools::FreeObjectFromMemory(token);
    exit(EXIT_FAILURE);
}

void Parser::ThrowErrorDataType(Token* token, std::string type_token, std::vector<std::string> expected_type)
{
    std::string allow_types;

    for(int i =0; i < expected_type.size(); i++)
    {
        if(i > 0) allow_types += " | ";
        allow_types += expected_type[i];
    }

    std::string lineError = "Line: " + std::to_string(token->line) + ", Col: " + std::to_string(token->startpos);
    Output::PrintCustomizeError("Syntax Error (" + lineError + "): ", "Cannot implicitly convert type '" + type_token + "' to '"+ allow_types +"'");
    MemTools::FreeObjectFromMemory(token);
    exit(EXIT_FAILURE);
}

void Parser::ThrowInternalError(std::string message)
{
    Output::PrintCustomizeError("Compiler internal error: ", message);
    exit(EXIT_FAILURE);
}

void Parser::ExpectType(TYPE_TOKEN expected, std::string message)
{
    auto token = this->GetNextToken(message);

    if(token != nullptr && token->type != expected)
        this->ThrowError(token, message);

    delete token;
}

void Parser::ExpectValue(std::string expected, std::string message)
{
    auto token = this->GetNextToken(message);

    if(token != nullptr && token->value != expected)
        this->ThrowError(token, message);

    if(token == nullptr)
    {
        Output::PrintCustomizeError("Line: " + std::to_string(lexer->lineCounter) + " | Syntax error: ", message);
        exit(EXIT_FAILURE);
    }

    delete token;
}

void Parser::PushToAst(AstBranch* node)
{
    this->ast->AddNode(node);
}

void Parser::InsertIdentifierIntoSymbolTable(VariableDeclaration* variable)
{
    if(variable != nullptr)
    {
        auto NewID = new IdentifierModel
        (
            variable->name, 
            variable->type, 
            variable->scopeName, 
            variable->deep,
            variable->isConstant
        );

        this->CheckMemoryAllocated(NewID);

        this->symbolTable->InsertIdentifier(NewID);
    }
}

Token* Parser::GetNextToken(std::string msg)
{
    std::string header = "Syntax Error (Line: "+std::to_string(this->lineHistory)+"): ";
    if(msg.empty()) msg = "the source code ends abruptly before closing compilaion";
    
    auto token = this->lexer->GetNextToken();

    if(token == nullptr) 
    {
        Output::PrintCustomizeError(header, msg);
        exit(EXIT_FAILURE);
    }

    this->lineHistory = token->line;

    return token;
}

std::string Parser::GenerateCallFunctionHash()
{
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return std::to_string(std::hash<std::string>{}(std::to_string(rand() % 9)));
}

std::vector<Tokens*> Parser::GetNewInstanceOfArgumentList(int ArgumentSize)
{
    std::vector<Tokens*> list;

    for(int i = 0; i < ArgumentSize; i++)
        list.push_back(new Tokens());

    return list;
}

TYPE_IDENTIFIER Parser::GetTypeIdentifier(Token* token, const std::vector<std::string> expected_type)
{
    auto isVariable = this->symbolTable->GetIdentifier(token->value, this->currentScope, this->currentDeep);
    
    if(isVariable != nullptr) 
    {
        if(expected_type.size() <= 0) return TYPE_IDENTIFIER::IDENTIFIER_VARIABLE;

        for(auto item : expected_type)
        {
            if(isVariable->type == item) 
                return TYPE_IDENTIFIER::IDENTIFIER_VARIABLE;
        }

        this->ThrowErrorDataType(token, isVariable->type, expected_type);
    }

    auto isCallFunction = this->symbolTable->GetFunctionIdentifier(token->value);

    if(isCallFunction != nullptr) 
    {   
        if(expected_type.size() <= 0) return TYPE_IDENTIFIER::IDENTIFIER_FUNCTION;

        for(auto item : expected_type)
        {
            if(isCallFunction->type == item) 
                return TYPE_IDENTIFIER::IDENTIFIER_FUNCTION;
        }
        
        this->ThrowErrorDataType(token, isCallFunction->type, expected_type);
    }

    return TYPE_IDENTIFIER::NOT_FOUND;
}

void Parser::ExpectThisToken(Token* token, std::string expected, std::string message)
{
    if(token->value != expected) ThrowError(token, message);
}

bool Parser::IsValidDataType(Token* token, std::vector<std::string> expected_type)
{
    if(expected_type.size() <= 0) return true;

    for(auto item : expected_type)
    {
        if(token->type == TYPE_TOKEN::T_FLOAT_LITERAL  && item == TYPE::T_FLOAT  ||
           token->type == TYPE_TOKEN::T_INT_LITERAL    && item == TYPE::T_INT    ||
           token->type == TYPE_TOKEN::T_BOOL_LITERAL   && item == TYPE::T_BOOL   ||
           token->type == TYPE_TOKEN::T_CHAR_LITERAL   && item == TYPE::T_CHAR   ||
           token->type == TYPE_TOKEN::T_STRING_LITERAL && item == TYPE::T_STRING )
        {
            return true;
        }
    }

    return false;
}

std::string Parser::ConvertTypeTokenToType(TYPE_TOKEN type)
{
    switch (type)
    {
        case TYPE_TOKEN::T_BOOL_LITERAL:
            return TYPE::T_BOOL;    
        
        case TYPE_TOKEN::T_CHAR_LITERAL:
            return TYPE::T_CHAR;    
        
        case TYPE_TOKEN::T_FLOAT_LITERAL:
            return TYPE::T_FLOAT;    
        
        case TYPE_TOKEN::T_INT_LITERAL:
            return TYPE::T_INT;    
        
        case TYPE_TOKEN::T_STRING_LITERAL:
            return TYPE::T_STRING;
        
        default:
            this->ThrowInternalError("Cannot convert Type Token");
            break;
    }

    return "";
}

std::vector<std::string> Parser::CreateExpectedType(std::string type)
{
    std::vector<std::string> tmpVec { type };
    return tmpVec;
}
















