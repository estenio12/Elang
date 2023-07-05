#include "../Include/Parser.hpp"

AstNode* Parser::ArithmeticOperation(Token* token, std::string expectedType)
{
    this->ArithmeticExpectedType = expectedType;
    
    if(history->value[0] == DELIMITERS::CLOSE_PARAM || 
       history->type == NAME::IDENTIFIER ||
       history->type == NAME::NUMBER     ||
       history->type == NAME::BOOLEAN    ||
       history->type == NAME::CHARACTER  ||
       history->type == NAME::STRING)
    {
        if(token->value == ARITHMETIC::ADD ||
           token->value == ARITHMETIC::SUB ||
           token->value == ARITHMETIC::DIV ||
           token->value == ARITHMETIC::MUL ||
           token->value == ARITHMETIC::MOD ||
           token->value == ARITHMETIC::AND ||
           token->value == ARITHMETIC::OR  ||
           token->value == ARITHMETIC::SHIFTLEFT  ||
           token->value == ARITHMETIC::SHIFTRIGHT )
        {
            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            this->history = token;

            return nullptr;
        }
    
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->history = token;
            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            this->RemoveParemCounter();
            return nullptr;
        }
    
        if(token->value[0] == DELIMITERS::EOL)
        {
            if(ArithmeticParemCounter > 0)
                this->ThrowError("The parentheses were opened, but never closed.", token->startPos);

            if(ArithmeticParemCounter < 0)
                this->ThrowError("The parentheses were closed, but never opened.", token->startPos);

            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            
            return this->ArithmeticBuildingNode;
        }
    }

    if(history->value[0] == DELIMITERS::ASSIGN     ||
       history->value[0] == DELIMITERS::OPEN_PARAM ||
       history->value == ARITHMETIC::ADD ||
       history->value == ARITHMETIC::SUB ||
       history->value == ARITHMETIC::DIV ||
       history->value == ARITHMETIC::MUL ||
       history->value == ARITHMETIC::MOD ||
       history->value == ARITHMETIC::AND ||
       history->value == ARITHMETIC::OR  ||
       history->value == ARITHMETIC::SHIFTLEFT  ||
       history->value == ARITHMETIC::SHIFTRIGHT )
    {
        if(this->ArithmeticOperationCheckIdentifier(token)) return nullptr;
        if(this->ArithmeticOperationCheckType(token)) return nullptr;
        if(this->ArithmeticOperationCheckOpenParam(token)) return nullptr;
    }

    this->ThrowError(token);
    return nullptr;
}

bool Parser::ArithmeticOperationCheckOpenParam(Token* token)
{
    if(token->value[0] == DELIMITERS::OPEN_PARAM)
    {
        this->AddParemCounter();
        this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

bool Parser::ArithmeticOperationCheckType(Token* token)
{
    if(token->type == NAME::NUMBER    ||
       token->type == NAME::BOOLEAN   ||
       token->type == NAME::CHARACTER ||
       token->type == NAME::STRING    )
    {
        if(token->type != this->ArithmeticExpectedType)
           this->ThrowError("Cannot implicitly convert type '" + token->type + "' to '" + this->ArithmeticExpectedType + "'", token->startPos + 1);

        this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

bool Parser::ArithmeticOperationCheckIdentifier(Token* token)
{
    if(token->type == NAME::IDENTIFIER)
    {
        if(!this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep))
            this->ThrowError("Variable not declared in scope '" + token->value + "'", token->startPos + 1);

        auto getEntity = this->IDTable->FindObjectIdentifier(token->value);

        if(getEntity == nullptr)
        {
            Output::PrintCustomizeError("Compiler internal error: ", "Object not found in IDTable");
            exit(EXIT_FAILURE);
        }

        if(getEntity->typeValue != this->ArithmeticExpectedType)
           this->ThrowError("Cannot implicitly convert type '" + getEntity->typeValue + "' to '" + this->ArithmeticExpectedType + "'", token->startPos + 1);

        this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

void Parser::InsertArithmeticNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->ArithmeticBuildingNode == nullptr)
    {
        this->ArithmeticBuildingNode = node;
        this->history = token;
    }
    else
    {
        auto lastNode = this->FindLastNode(ArithmeticBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetArithmeticBuildingNode()
{
    this->ArithmeticBuildingNode = nullptr;
}










