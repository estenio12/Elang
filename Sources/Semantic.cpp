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

    this->PrintError("Unexpected | " + Token.second);

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
            this->SemanticDeclaratorItsAssigned = false;

            return true;
        }

        if(Token.second == KEYWORDS::Declarator[KEYWORDS::EDeclarator::CONST])
        {
            this->SetSemanticHistory(Token);
            this->SemanticDeclaratorIsUp = true;
            this->SemanticDeclaratorItsAssigned = false;
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
    if(this->SemanticHistory.first == NAMES::IDENTIFIER && !SemanticDeclaratorItsAssigned)
    {
        if(Token.second == LANG::STMT[LANG::TYPEASSIGNMENT])
        {
            this->SetSemanticHistory(Token);
            this->SemanticDeclaratorItsAssigned = true;

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
            this->IDTable->SetType(TYPE::NUMBER, CurrentIdentifier);

            return true;
        }

        if(Token.second == KEYWORDS::Type[KEYWORDS::EType::BOOL])
        {
            this->SetSemanticHistory(Token);
            this->IDTable->SetType(TYPE::BOOL, CurrentIdentifier);

            return true;
        }

        if(Token.second == KEYWORDS::Type[KEYWORDS::EType::CHAR])
        {
            this->SetSemanticHistory(Token);
            this->IDTable->SetType(TYPE::CHAR, CurrentIdentifier);

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
            this->SemanticDeclaratorItsAssigned = true;

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
    if(this->SemanticHistory.second == 
        KEYWORDS::Assignment[KEYWORDS::EAssignment::ASSIGNMENT] ||
       this->SemanticHistory.second == 
        KEYWORDS::Assignment[KEYWORDS::EAssignment::PLUS] ||
       this->SemanticHistory.second == 
        KEYWORDS::Assignment[KEYWORDS::EAssignment::LESS] ||
       this->SemanticHistory.second == 
        KEYWORDS::Assignment[KEYWORDS::EAssignment::MUL]  ||
       this->SemanticHistory.second == 
        KEYWORDS::Assignment[KEYWORDS::EAssignment::DIV]  || 
       this->SemanticHistory.first == NAMES::RELATIONAL           || 
       this->SemanticHistory.first == NAMES::LOGICAL)
    {
        if(Token.second == LANG::STMT[LANG::OPENPAREM])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(this->IDTable->CheckIfExistIdentifier(Token.second))
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.first == NAMES::NUMBER)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == KEYWORDS::VALUE[KEYWORDS::EValues::TRUE] ||
           Token.second == KEYWORDS::VALUE[KEYWORDS::EValues::FALSE])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
        
        return false;
    }

    if(this->SemanticHistory.first == NAMES::IDENTIFIER ||
       this->SemanticHistory.first == NAMES::NUMBER || 
       this->SemanticHistory.first == NAMES::VALUE)
    {
        if(Token.second == LANG::STMT[LANG::ENDOFLINE])
        {
            this->SemanticCloseDeclaration();

            return true;
        }

        if(Token.second == LANG::STMT[LANG::CLOSEPAREM])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::PLUS] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::LESS] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::DIV] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::MUL])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.first == NAMES::RELATIONAL)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.first == NAMES::LOGICAL)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
        return false;
    }

    if(this->SemanticHistory.second == LANG::STMT[LANG::CLOSEPAREM])
    {
        if(Token.second == LANG::STMT[LANG::ENDOFLINE])
        {
            this->SemanticCloseDeclaration();

            return true;
        }

        if(Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::PLUS] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::LESS] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::DIV] || 
           Token.second == 
            KEYWORDS::Assignment[KEYWORDS::EAssignment::MUL])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.first == NAMES::RELATIONAL)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.first == NAMES::LOGICAL)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(this->SemanticHistory.second == LANG::STMT[LANG::CLOSEPAREM])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
        
        return false;
    }

    if(this->SemanticHistory.second == LANG::STMT[LANG::OPENPAREM])
    {
        if(this->IDTable->CheckIfExistIdentifier(Token.second) ||
           Token.first == NAMES::NUMBER || 
           Token.first == NAMES::VALUE)
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        if(Token.second == LANG::STMT[LANG::OPENPAREM])
        {
            this->SetSemanticHistory(Token);

            return true;
        }

        this->PrintError("Unexpected operator | " + Token.second);
        
        return false;
    }

    if(this->SemanticHistory.second == LANG::STMT[LANG::ENDOFLINE])
    {
        this->SemanticCloseDeclaration();

        return true;
    }

    return false;
}
