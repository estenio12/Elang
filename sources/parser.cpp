#include "../headers/parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    debug = new DebugCompiler();
}

Parser::~Parser(){}

void Parser::Parse()
{
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

        auto operation = this->BindOperation(token);

        switch(operation)
        {
            case BRANCH_TYPE::VARIABLE_DECLARATION:
                PushToAst(this->BuildVariableDeclaration(token));
            break;
            
            default:
                ThrowInternalError("Parser operation not implemented!");
            break;
        }
    }
}

void Parser::ThrowError(Token* token, std::string message)
{
    std::string lineError = std::to_string(token->line) + ":" + std::to_string(token->startpos);
    Output::PrintCustomizeError("Syntax Error: ", message + " '" + token->value + "'");
    Output::PrintCustomizeError("line: ", lineError);
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
        this->ThrowError(token, "Unexpected token");

    delete token;
}

void Parser::ExpectValue(std::string expected, std::string message)
{
    auto token = this->lexer->GetNextToken();

    if(token != nullptr && token->value != expected)
        this->ThrowError(token, "Unexpected token");

    delete token;
}

void Parser::PushToAst(AstBranch* node)
{
    debug->PrintAstBranch(node);
}







