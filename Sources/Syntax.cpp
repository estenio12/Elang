#include "../Includes/Parser.hpp"

void Parser::SyntaxCheck(Dictionary Token)
{
    switch(this->Level)
    {
        case 0:
            if(!this->ValidateDeclarations(Token)) this->ExitProgram();
        break;
    }
}

bool Parser::ValidateDeclarations(Dictionary Token)
{
    if(this->CheckDeclaration(Token)) return true;
    if(this->CheckDeclarationDeclarator(Token)) return true;
    if(this->CheckDeclarationIdentfier(Token)) return true;
    if(this->CheckDeclarationTypeAssign(Token)) return true;
    if(this->CheckDeclarationType(Token)) return true;

    this->PrintError("Syntax error | Unexpected " + Token.second);

    return false;
}

bool Parser::CheckDeclaration(Dictionary Token)
{
    if(this->History.first.empty())
    {
        if(Token.first == NAMES::DECLARATOR)
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Syntax error | Expected a declarator.");

    }

    return false;
}

bool Parser::CheckDeclarationDeclarator(Dictionary Token)
{
    if(this->History.first == NAMES::DECLARATOR)
    {
        if(Token.first == NAMES::IDENTIFIER)
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Syntax error | Expected a identifier after 'declarators'.");

    }

    return false;
}

bool Parser::CheckDeclarationIdentfier(Dictionary Token)
{
    if(this->History.first == NAMES::IDENTIFIER)
    {
        if(Token.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT])
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Syntax error | Expected a type assignment ':' after Identifier.");
    }

    return false;
}

bool Parser::CheckDeclarationTypeAssign(Dictionary Token)
{
    if(this->History.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT])
    {
        if(Token.first == NAMES::TYPE)
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Syntax error | Expected a type specifier.");
    }
    
    return false;
}

bool Parser::CheckDeclarationType(Dictionary Token)
{
    if(this->History.first == NAMES::TYPE)
    {
        if(Token.first == NAMES::ASSIGNMENT)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Syntax error | Expected an '=' or ';' after type specifier.");
    }

    return false;
}
