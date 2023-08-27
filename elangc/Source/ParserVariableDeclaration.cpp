#include "../Include/Parser.hpp"

AstNode* Parser::VariableDeclaration(Token* token)
{
    if(this->VariableDeclarationDeclarationState == BRANCH_IDENTIFIER::EXPRESSION)
    {
        auto result = this->Expression(token, this->expectedType);
        
        if(result != nullptr)
        {
            this->VariableDeclarationDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->VariableDeclarationBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetExpressionBuildingNode();
                return this->VariableDeclarationBuildingNode;
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Variable declaration structure not found!");
            }
        }

        return nullptr;
    }

    // # If history is null, is expected the variables declaration 
    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TVAR )
        {
            
            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }

        if(token->value == KEYWORDS::TCONST )
        {
            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->isConstant = true;
            this->history = token;
            return nullptr;
        }

        this->ThrowError(token);
    }

    // # After variables declaration token, is expected the colon 
    if(history->value == KEYWORDS::TVAR   ||
       history->value == KEYWORDS::TCONST )
    {
        if(token->value[0] == DELIMITERS::COLON)
        {
            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
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
            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history      = token;
            this->expectedType = this->GetExpectedTypeByValue(token);
            return nullptr;
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
            if(this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep))
               this->ThrowError("Duplicate variable declaration", token->startPos);

            if(token->value == KEYWORDS::TINDEX)   
               this->ThrowError("'index' is a reserved keyword.", token->startPos);

            int IDScope = this->IDTableScope->GetCurrentID();
            auto tempID = this->IDTable->CreateRow(token->value, token->value, token->type, this->expectedType,
                                                   this->currentScope, IDScope, this->currentDeep, this->isConstant);
            this->IDTable->InsertID(tempID);

            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }

        this->ThrowError(token);
    }

    // # After identifier token, is expected '=' or ';'
    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::ASSIGN)
        {
            // this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->VariableDeclarationDeclarationState = BRANCH_IDENTIFIER::EXPRESSION;
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = nullptr;
            return nullptr;
        }
        
        if(token->value[0] == DELIMITERS::EOL)
        {
            this->InsertVariableDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->VariableDeclarationCommit();
            return nullptr;
        }

        this->ThrowError(token);
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::VariableDeclarationCommit()
{
    this->InsertAstNode(BRANCH_NAME::VARIABLE_DECLARATION, this->VariableDeclarationBuildingNode);
    this->ResetState();
}

void Parser::InsertVariableDeclarationNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(VariableDeclarationBuildingNode == nullptr)
    {
        VariableDeclarationBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(VariableDeclarationBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetVariableDeclarationBuildingNode()
{
    this->VariableDeclarationBuildingNode = nullptr;
}


