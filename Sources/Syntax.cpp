#include "../Includes/Parser.hpp"

bool Parser::SintaxCheck(Dictionary Token)
{
    if(Level == 0)
    {
        if(this->CheckEmptyHistory(Token)) return true;
        if(this->CheckDeclaratorHistory(Token)) return true;
        if(this->CheckDeclaratorTypeAssignmentHistory(Token)) return true;
        if(this->CheckDeclaratorTypeHistory(Token)) return true;
        if(this->CheckDataAssignmentHistory(Token)) return true;
        if(this->CheckValueHistory(Token)) return true;
        if(this->CheckNumberHistory(Token)) return true;
        if(this->CheckIdentifierHistory(Token)) return true;
    }

    return false;
}

bool Parser::CheckEmptyHistory(Dictionary& Token)
{
    if(History.first.empty())
    {
        if(Token.first == NAMES::DECLARATOR) 
        { 
            this->DeclaratorIsUp = true;
            this->History = Token;

            return true; 
        }

        Console::PrintError("Sintax error | Expected a declarator | " + Token.second);
        this->ExitProgram();

        return false;
    }

    return false;
}

bool Parser::CheckDeclaratorHistory(Dictionary& Token)
{
    if(History.first == NAMES::DECLARATOR)
    {
        if(Token.first == NAMES::IDENTIFIER) 
        {
            this->History = Token;

            return true; 
        }

        Console::PrintError("Sintax error |  Expected a Identifier | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckDeclaratorTypeAssignmentHistory(Dictionary& Token)
{
    if(History.first == NAMES::IDENTIFIER)
    {
        if(Token.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT]) 
        {
            this->History = Token;

            return true; 
        }

        Console::PrintError("Sintax error | Expected a type assignment | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckDeclaratorTypeHistory(Dictionary& Token)
{
    if(History.first == LANG::STMTNAME[LANG::TYPEASSIGNMENT])
    {
        if(Token.first == NAMES::TYPE) 
        {
            this->History = Token;

            return true; 
        }

        Console::PrintError("Sintax error | Expected a type specifier | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckDeclaratorBranchHistory(Dictionary& Token)
{
    if(History.first == NAMES::TYPE)
    {
        if(Token.first == LANG::STMTNAME[LANG::ENDOFLINE]) 
        {
            this->RemoveHistory();
            this->DeclaratorIsUp = false;

            return true; 
        }

        if(Token.first == KEYWORDS::Assignment[KEYWORDS::ASSIGN])
        {
            this->History = Token;

            return true;
        }

        Console::PrintError("Sintax error | Expected a ';' or '=' | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckDataAssignmentHistory(Dictionary& Token)
{
    if(History.first == KEYWORDS::Assignment[KEYWORDS::ASSIGN])
    {
        if(Token.first == NAMES::NUMBER || 
           Token.first == NAMES::IDENTIFIER ||
           Token.first == NAMES::VALUE)
        {
            this->History = Token;

            return true;
        }

        Console::PrintError("Sintax error | Expected a data or identifier or operation | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckValueHistory(Dictionary& Token)
{
    if(History.first == NAMES::VALUE)
    {
        if(Token.first == LANG::STMTNAME[LANG::CLOSEPARAM] ||
           Token.first == LANG::STMTNAME[LANG::SEPARATE] ||
           Token.first == LANG::STMTNAME[LANG::CLOSEPARAM] ||
           Token.first == LANG::STMTNAME[LANG::ENDOFLINE])
        {
            this->History = Token;

            return true;
        }

        Console::PrintError("Sintax error | Unexpected a value | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckNumberHistory(Dictionary& Token)
{
    if(History.first == NAMES::NUMBER)
    {
        if(Token.first == NAMES::ASSIGNMENT ||
           Token.first == NAMES::RELATIONAL ||
           Token.first == NAMES::LOGICAL ||
           Token.first == LANG::STMTNAME[LANG::ENDOFLINE] ||
           Token.first == LANG::STMTNAME[LANG::CLOSEBRACE] ||
           Token.first == LANG::STMTNAME[LANG::CLOSEBRACKET] ||
           Token.first == LANG::STMTNAME[LANG::SEPARATE])
        {
            this->History = Token;

            return true;
        }

        Console::PrintError("Sintax error | Invalid operator in this place | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

bool Parser::CheckIdentifierHistory(Dictionary& Token)
{
    if(History.first == NAMES::IDENTIFIER)
    {
        if(Token.first == NAMES::ASSIGNMENT ||
           Token.first == NAMES::RELATIONAL ||
           Token.first == NAMES::LOGICAL ||
           Token.first == LANG::STMTNAME[LANG::ENDOFLINE] ||
           Token.first == LANG::STMTNAME[LANG::CLOSEBRACE] ||
           Token.first == LANG::STMTNAME[LANG::CLOSEBRACKET] ||
           Token.first == LANG::STMTNAME[LANG::SEPARATE])
        {
            this->History = Token;

            return true;
        }

        Console::PrintError("Sintax error | Invalid operator in this place | " + Token.second);
        this->ExitProgram();
        
        return false;
    }

    return false;
}

