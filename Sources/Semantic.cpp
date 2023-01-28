#include "../Includes/Parser.hpp"

#include "../Includes/Parser.hpp"

void Parser::SemanticCheck(Dictionary Token)
{
    switch(this->Level)
    {
        case 0:
            if(!this->SemanticValidateDeclarations(Token)) this->ExitProgram();
        break;
    }
}

bool Parser::SemanticValidateDeclarations(Dictionary& Token)
{
    if(this->SemanticCheckDeclaration(Token)) return true;
    if(this->SemanticCheckDeclarationDeclarator(Token)) return true;
    if(this->SemanticCheckDeclarationIdentfier(Token)) return true;
    if(this->SemanticCheckDeclarationTypeAssign(Token)) return true;
    if(this->SemanticCheckDeclarationType(Token)) return true;
    if(this->SemanticCheckOperation(Token)) return true;

    this->PrintError("Unexpected " + Token.second);

    return false;
}

bool Parser::SemanticCheckDeclaration(Dictionary Token)
{
    if(this->SemanticHistory.first.empty())
    {
        if(Token.second == KEYWORDS::Declarator[KEYWORDS::EDeclarator::VAR])
        {
            this->SetSemanticHistory(Token);
            this->SemanticDeclaratorIsUp = true;

            return true;
        }

        if(Token.second == KEYWORDS::Declarator[KEYWORDS::EDeclarator::CONST])
        {
            this->SetSemanticHistory(Token);
            this->SemanticDeclaratorIsUp = true;
            this->ItsConstant = true;

            return true;
        }

        this->PrintError("Unexpected declarator | " + Token.second);
    }

    return false;
}

bool Parser::SemanticCheckDeclarationDeclarator(Dictionary Token)
{
    if(this->SemanticHistory.first == NAMES::DECLARATOR)
    {
        if(Token.first == NAMES::IDENTIFIER)
        {
            if(IDTable->CheckIfExistIdentifier(Token.second))
            {
                this->PrintError("Duplicate identifier, previously declared identifier | " + Token.second);
                this->ExitProgram();
            }

            this->IDTable->CreateID(Token.second);
            this->SetCurrentIdentifier(Token.second);
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Expected a identifier after 'declarators'.");
    }

    return false;
}

bool Parser::SemanticCheckDeclarationIdentfier(Dictionary Token)
{
    if(this->SemanticHistory.first == NAMES::IDENTIFIER)
    {
        if(Token.second == LANG::STMT[LANG::TYPEASSIGNMENT])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Expected a type assignment ':' after Identifier.");
    }

    return false;
}

bool Parser::SemanticCheckDeclarationTypeAssign(Dictionary Token)
{
    if(this->SemanticHistory.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT])
    {
        if(Token.second == KEYWORDS::Type[KEYWORDS::EType::NUMBER])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == KEYWORDS::Type[KEYWORDS::EType::BOOL])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == KEYWORDS::Type[KEYWORDS::EType::CHAR])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Expected a type specifier | " + Token.second);
    }
    
    return false;
}

bool Parser::SemanticCheckDeclarationType(Dictionary Token)
{
    if(this->SemanticHistory.first == NAMES::TYPE)
    {
        if(Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::ASSIGNMENT])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == LANG::STMT[LANG::ENDOFLINE])
        {
            this->SemanticCloseDeclaration();

            return true;
        }

        this->PrintError("Expected an '=' or ';' after type specifier.");
    }

    return false;
}

bool Parser::SemanticCheckOperation(Dictionary Token)
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
