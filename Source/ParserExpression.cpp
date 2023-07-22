#include "../Include/Parser.hpp"

AstNode* Parser::Expression(Token* token, std::string expectedType)
{
    this->ExpressionExpectedType = expectedType;

    if(history == nullptr ||
       history->value[0] == DELIMITERS::COMMA)
    {
        if(this->ExpressionCheckIdentifier(token)) return nullptr;
        if(this->ExpressionCheckType(token)) return nullptr;
        if(this->ExpressionCheckOpenParam(token)) return nullptr;

        this->ThrowError(token);
    }

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
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = token;

            return nullptr;
        }
    
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->history = token;
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->RemoveParemCounter();
            return nullptr;
        }
    
        if(token->value[0] == DELIMITERS::EOL)
        {
            if(ExpressionParemCounter > 0)
                this->ThrowError("The parentheses were opened, but never closed.", token->startPos);

            if(ExpressionParemCounter < 0)
                this->ThrowError("The parentheses were closed, but never opened.", token->startPos);

            if(this->ExpressionCommaCounter > 0)
                this->ThrowError("too few arguments to function.", token->startPos);

            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            
            return this->ExpressionBuildingNode;
        }
    
        if(history->type == NAME::IDENTIFIER && history->isFunID == true)
        {
            if(this->ExpressionCheckOpenParam(token)) return nullptr;
        }

        if(token->value[0] == DELIMITERS::COMMA)
        {
            if(this->ExpressionCommaCounter <= 0) this->ThrowError(token);
            this->DecrementExpressionCommaCounter();
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }
    }

    if(history->value[0] == DELIMITERS::OPEN_PARAM ||
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
        if(this->ExpressionCheckIdentifier(token)) return nullptr;
        if(this->ExpressionCheckType(token)) return nullptr;
        if(this->ExpressionCheckOpenParam(token)) return nullptr;
    }

    this->ThrowError(token);
    return nullptr;
}

bool Parser::ExpressionCheckOpenParam(Token* token)
{
    if(token->value[0] == DELIMITERS::OPEN_PARAM)
    {
        this->AddParemCounter();
        this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

bool Parser::ExpressionCheckType(Token* token)
{
    if(token->type == NAME::NUMBER    ||
       token->type == NAME::BOOLEAN   ||
       token->type == NAME::CHARACTER ||
       token->type == NAME::STRING    )
    {
        if(token->type != this->ExpressionExpectedType)
           this->ThrowError("Cannot implicitly convert type '" + token->type + "' to '" + this->ExpressionExpectedType + "'", token->startPos + 1);

        this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

bool Parser::ExpressionCheckIdentifier(Token* token)
{
    if(token->type == NAME::IDENTIFIER)
    {
        if(this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep))
        {
            auto getEntity = this->IDTable->FindObjectIdentifier(token->value);

            if(getEntity == nullptr)
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Object not found in IDTable");
                exit(EXIT_FAILURE);
            }

            if(getEntity->typeValue != this->ExpressionExpectedType)
               this->ThrowError("Cannot implicitly convert type '" + getEntity->typeValue + "' to '" + this->ExpressionExpectedType + "'", token->startPos + 1);
        }
        else if(this->IDFunTable->ExistIdentifier(token->value))
        {
            auto getEntity = this->IDFunTable->FindObjectIdentifier(token->value);

            if(getEntity == nullptr)
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Object not found in IDFunTable");
                exit(EXIT_FAILURE);
            }

            this->IncrementExpressionCommaCounter(getEntity->paramList.size());

            if(getEntity->type != this->ExpressionExpectedType)
               this->ThrowError("Cannot implicitly convert type '" + getEntity->type + "' to '" + this->ExpressionExpectedType + "'", token->startPos + 1);

            token->isFunID = true;
        }
        else
        {
            this->ThrowError("Identifier not declared in scope '" + token->value + "'", token->startPos + 1);
        }

        this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

void Parser::InsertExpressionNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(this->ExpressionBuildingNode == nullptr)
    {
        this->ExpressionBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(ExpressionBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetExpressionBuildingNode()
{
    this->ExpressionBuildingNode = nullptr;
}

void Parser::IncrementExpressionCommaCounter(int value)
{
    value--;
    this->ExpressionCommaCounter += value;
}

void Parser::DecrementExpressionCommaCounter()
{
    this->ExpressionCommaCounter--;
}



