#include "../headers/parser.hpp"

Parser::Parser(Lexer* lexer, SymbolTable* symbolTable, Ast* ast):lexer(lexer), symbolTable(symbolTable), ast(ast)
{
    debug = new DebugCompiler();
}

Parser::~Parser()
{
    delete this->debug;
}

void Parser::Parse()
{
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
            break;
            
            default:
                ThrowInternalError("Parser operation not implemented!");
            break;
        }
    }
}

void Parser::ThrowError(Token* token, std::string message)
{
    std::string lineError = "Line: " + std::to_string(token->line) + ", Col: " + std::to_string(token->startpos);
    Output::PrintCustomizeError("Syntax Error (" + lineError + "): ", message + " '" + token->value + "'");
    delete token;
    exit(EXIT_FAILURE);
}

void Parser::ThrowInternalError(std::string message)
{
    Output::PrintCustomizeError("Compiler internal error: ", message);
    exit(EXIT_FAILURE);
}

void Parser::ExpectType(TYPE_TOKEN expected, std::string message)
{
    auto token = this->lexer->GetNextToken();

    if(token != nullptr && token->type != expected)
        this->ThrowError(token, message);

    delete token;
}

void Parser::ExpectValue(std::string expected, std::string message)
{
    auto token = this->lexer->GetNextToken();

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
    // debug->PrintAstBranch(node);
}

void Parser::InsertIdentifierIntoSymbolTable(AstBranch* node)
{
    if(node != nullptr && node->TYPE == EBRANCH_TYPE::VARIABLE_DECLARATION)
    {
        auto variable = node->branch_variable_declaration;

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












