#include "../headers/parser.hpp"

Parser::Parser(Lexer* lexer, SymbolTable* symbolTable, Ast* ast):lexer(lexer), symbolTable(symbolTable), ast(ast){}

Parser::~Parser(){}

Ast* Parser::Parse()
{
    // # Passing
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

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
    Output::PrintCustomizeError("Syntax Error (" + lineError + "): ", message + " '" + token->value + "'");
    MemTools::FreeObjectFromMemory(token);
    exit(EXIT_FAILURE);
}

void Parser::ThrowErrorDataType(Token* token, std::string type_token, std::string expected_type)
{
    std::string lineError = "Line: " + std::to_string(token->line) + ", Col: " + std::to_string(token->startpos);
    Output::PrintCustomizeError("Syntax Error (" + lineError + "): ", "Cannot implicitly convert type '" + type_token + "' to '"+ expected_type +"'");
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

TYPE_IDENTIFIER Parser::GetTypeIdentifier(Token* token, std::string expected_type)
{
    auto isVariable = this->symbolTable->GetIdentifier(token->value, this->currentScope, this->currentDeep);
    
    if(isVariable != nullptr) 
    {
        if(isVariable->type != expected_type) this->ThrowErrorDataType(token, isVariable->type, expected_type);
        return TYPE_IDENTIFIER::IDENTIFIER_VARIABLE;
    }

    auto isCallFunction = this->symbolTable->GetFunctionIdentifier(token->value);

    if(isCallFunction != nullptr) 
    {
        if(isCallFunction->type != expected_type) this->ThrowErrorDataType(token, isCallFunction->type, expected_type);
        return TYPE_IDENTIFIER::IDENTIFIER_FUNCTION;
    }

    return TYPE_IDENTIFIER::NOT_FOUND;
}

void Parser::ExpectThisToken(Token* token, std::string expected, std::string message)
{
    if(token->value != expected) ThrowError(token, message);
}

void Parser::CheckDataType(Token* token, std::string expected_type)
{
    if(token->type == TYPE_TOKEN::T_FLOAT_LITERAL  && expected_type == TYPE::T_FLOAT  ||
       token->type == TYPE_TOKEN::T_INT_LITERAL    && expected_type == TYPE::T_INT    ||
       token->type == TYPE_TOKEN::T_BOOL_LITERAL   && expected_type == TYPE::T_BOOL   ||
       token->type == TYPE_TOKEN::T_CHAR_LITERAL   && expected_type == TYPE::T_CHAR   ||
       token->type == TYPE_TOKEN::T_STRING_LITERAL && expected_type == TYPE::T_STRING )
    {
        return;
    }

    this->ThrowErrorDataType(token, ConvertTypeTokenToType(token->type), expected_type);
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









