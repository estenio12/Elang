#include "../Include/Parser.hpp"

bool Parser::VariableDeclaration(Token* token)
{
    // # If history is null, is expected the variables declaration 
    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TVAR )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        if(token->value == KEYWORDS::TCONST )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->isConstant = true;
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    // # After variables declaration token, is expected the colon 
    if(history->value == KEYWORDS::TVAR   ||
       history->value == KEYWORDS::TCONST )
    {
        if(token->value[0] == DELIMITERS::COLON)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    // # After colon token, is expected a type
    if(history->value[0] == DELIMITERS::COLON)
    {
        if(token->value == TYPE::NAME[TYPE::TBOOL]   ||
           token->value == TYPE::NAME[TYPE::TCHAR]   ||
           token->value == TYPE::NAME[TYPE::TNUMBER] ||
           token->value == TYPE::NAME[TYPE::TTEXT]   ||
           token->value == TYPE::NAME[TYPE::TVOID]   )
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history      = token;
            this->expectedType = this->GetTypeVariableDeclaration(token);
            return true;
        }

        this->ThrowError(token);
    }

    // # After type token, is expected an identifier 
    if(history->value == TYPE::NAME[TYPE::TBOOL]   ||
       history->value == TYPE::NAME[TYPE::TCHAR]   ||
       history->value == TYPE::NAME[TYPE::TNUMBER] ||
       history->value == TYPE::NAME[TYPE::TTEXT]   ||
       history->value == TYPE::NAME[TYPE::TVOID]   )
    {
        if(token->type == NAME::IDENTIFIER)
        {
            if(this->IDTable->ExistIdentifier(token->value))
               this->ThrowError("Duplicate variable declaration", token->startPos);

            auto tempID = this->IDTable->CreateRow(token->value, token->value, token->type, this->expectedType,
                                                   this->currentScope, this->currentDeep, this->isConstant);
            this->IDTable->InsertID(tempID);

            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    // # After identifier token, is expected '=' or ';'
    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::ASSIGN)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->currentBranch = BRANCH_IDENTIFIER::ARITHMETIC_OPERATION;
            return true;
        }
        
        if(token->value[0] == DELIMITERS::EOL)
        {
            this->InsertBuildingNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->VariableDeclarationCommit();
            return true;
        }

        this->ThrowError(token);
    }

    return false;
}

void Parser::VariableDeclarationCommit()
{
    this->InsertAstNode(BRANCH_NAME::VARIABLE_DECLARATION, this->buildingNode);
    this->ResetState();
}

std::string Parser::GetTypeVariableDeclaration(Token* token)
{
    if(token->value == TYPE::NAME[TYPE::TBOOL]) return EXPECTED_TYPE::TBOOLEAN;
    if(token->value == TYPE::NAME[TYPE::TCHAR]) return EXPECTED_TYPE::TCHARACTER;
    if(token->value == TYPE::NAME[TYPE::TNUMBER]) return EXPECTED_TYPE::TNUMBER;
    if(token->value == TYPE::NAME[TYPE::TTEXT]) return EXPECTED_TYPE::TSTRING;
    if(token->value == TYPE::NAME[TYPE::TVOID]) return EXPECTED_TYPE::TVOID;

    Output::PrintCustomizeError("Compiler internal error: ", "No match type in variable declaration");
    exit(EXIT_FAILURE);
}

