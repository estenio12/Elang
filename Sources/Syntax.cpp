#include "../Includes/Parser.hpp"

void Parser::SyntaxCheck(Dictionary Token)
{
    switch(this->Level)
    {
        case 0:
            if(!this->SyntaxValidateDeclarations(Token)) this->ExitProgram();
        break;
    }
}

bool Parser::SyntaxValidateDeclarations(Dictionary& Token)
{
    if(this->SyntaxCheckDeclaration(Token)) return true;
    if(this->SyntaxCheckDeclarationDeclarator(Token)) return true;
    if(this->SyntaxCheckDeclarationIdentfier(Token)) return true;
    if(this->SyntaxCheckDeclarationTypeAssign(Token)) return true;
    if(this->SyntaxCheckDeclarationType(Token)) return true;
    if(this->SyntaxCheckOperation(Token)) return true;

    this->PrintError("Syntax error | Unexpected " + Token.second);

    return false;
}

bool Parser::SyntaxCheckDeclaration(Dictionary Token)
{
    if(this->History.first.empty())
    {
        if(Token.first == NAMES::DECLARATOR)
        {
            this->SetHistory(Token);
            this->DeclaratorIsUp = true;
            this->DeclaratorItsAssigned = false;

            return true;
        }

        this->PrintError("Syntax error | Expected a declarator | " + Token.second);
    }

    return false;
}

bool Parser::SyntaxCheckDeclarationDeclarator(Dictionary Token)
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

bool Parser::SyntaxCheckDeclarationIdentfier(Dictionary Token)
{
    if(this->History.first == NAMES::IDENTIFIER && !this->DeclaratorItsAssigned)
    {
        if(Token.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT])
        {
            this->SetHistory(Token);
            this->DeclaratorItsAssigned = true;

            return true;
        }

        this->PrintError("Syntax error | Expected a type assignment ':' after Identifier.");
    }

    return false;
}

bool Parser::SyntaxCheckDeclarationTypeAssign(Dictionary Token)
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

bool Parser::SyntaxCheckDeclarationType(Dictionary Token)
{
    if(this->History.first == NAMES::TYPE)
    {
        if(Token.first == NAMES::ASSIGNMENT)
        {
            this->SetHistory(Token);
            this->DeclaratorItsAssigned = true;

            return true;
        }

        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->CloseDeclaration();
            this->DeclaratorItsAssigned = false;

            return true;
        }

        this->PrintError("Syntax error | Expected an '=' or ';' after type specifier.");
    }

    return false;
}

bool Parser::SyntaxCheckOperation(Dictionary Token)
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
        
        if(Token.first == LANG::STMTNAME[LANG::CLOSEPAREM])
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
        if(Token.first == LANG::STMTNAME[LANG::OPENPAREM])
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

    if(this->History.first == LANG::STMTNAME[LANG::CLOSEPAREM])
    {
        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->CloseDeclaration();

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

        if(Token.first == LANG::STMTNAME[LANG::CLOSEPAREM])
        {   
            this->SetHistory(Token);
            this->RemoveParanOpen();

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
    }

    if(this->History.first == LANG::STMTNAME[LANG::OPENPAREM])
    {
        if(Token.first == NAMES::IDENTIFIER ||
           Token.first == NAMES::NUMBER ||
           Token.first == NAMES::VALUE)
        {
            this->SetHistory(Token);

            return true;
        }

        if(Token.first == LANG::STMTNAME[LANG::OPENPAREM])
        {
            this->SetHistory(Token);
            this->AddParanOpen();

            return true;
        }

        this->PrintError("Expected a data after '(' | " + Token.second);
    }

    return false;
}
