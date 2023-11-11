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
            variable->deep
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

TYPE_IDENTIFIER Parser::GetTypeIdentifier(Token* token)
{
    auto isVariable = this->symbolTable->ExistsIdentifier(token->value, this->currentScope, this->currentDeep);
    if(isVariable) return TYPE_IDENTIFIER::IDENTIFIER_VARIABLE;

    auto isCallFunction = this->symbolTable->ExistsFunctionIdentifier(token->value);
    if(isCallFunction) return TYPE_IDENTIFIER::IDENTIFIER_FUNCTION;

    return TYPE_IDENTIFIER::NOT_FOUND;
}

void Parser::ExpectThisToken(Token* token, std::string expected, std::string message)
{
    if(token->value != expected) ThrowError(token, message);
}











