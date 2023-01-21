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

bool Parser::ValidateDeclarations(Dictionary& Token)
{
    if(this->CheckDeclaration(Token)) return true;
    if(this->CheckDeclarationDeclarator(Token)) return true;
    if(this->CheckDeclarationIdentfier(Token)) return true;
    if(this->CheckDeclarationTypeAssign(Token)) return true;
    if(this->CheckDeclarationType(Token)) return true;
    if(this->CheckOperation(Token)) return true;

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
            this->DeclaratorIsUp = true;

            return true;
        }

        this->PrintError("Syntax error | Expected a declarator | " + Token.second);
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

bool Parser::CheckOperation(Dictionary Token)
{
    if(this->History.first == NAMES::IDENTIFIER || 
       this->History.first == NAMES::NUMBER || 
       this->History.first == NAMES::VALUE )
    {
        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->CloseDeclaration();

            return true;
        }
        
        if(Token.first == LANG::STMTNAME[LANG::CLOSEPARAM])
        {
            this->SetHistory(Token);
            this->RemoveParanOpen();

            return true;
        }

        if(Token.first == NAMES::ASSIGNMENT)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::RELATIONAL)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::LOGICAL)
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
        
        return false;
    }

    if(this->History.first == NAMES::ASSIGNMENT ||
       this->History.first == NAMES::RELATIONAL || 
       this->History.first == NAMES::LOGICAL )
    {
        if(Token.first == LANG::STMTNAME[LANG::OPENPARAM])
        {
            this->SetHistory(Token);
            this->AddParanOpen();

            return true;
        }

        if(Token.first == NAMES::IDENTIFIER)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::NUMBER)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::VALUE)
        {
            this->SetHistory(Token);

            return true;
        }

        this->PrintError("Expected a value | " + Token.second);

        return false;
    }

    if(this->History.first == LANG::STMTNAME[LANG::CLOSEPARAM])
    {
        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->CloseDeclaration();

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
    }

    if(this->History.first == LANG::STMTNAME[LANG::OPENPARAM])
    {
        if(Token.first == NAMES::IDENTIFIER)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::NUMBER)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == NAMES::VALUE)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == LANG::STMTNAME[LANG::OPENPARAM])
        {
            this->SetHistory(Token);
            this->AddParanOpen();

            return true;
        }

        this->PrintError("Expected a data after '(' | " + Token.second);
    }

    return false;
}
