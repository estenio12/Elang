#include "../Include/Parser.hpp"

AstNode* Parser::Expression(Token* token, std::string expectedType)
{
    if(!this->ExpressionDoOnce) 
    {
        this->ExpressionExpectedType = expectedType;
        this->ExpressionDoOnce = true;
    }

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
       history->type == NAME::CHAR       ||
       history->type == NAME::TEXT       ||
       history->type == NAME::IO_SYSTEM  ||
       history->type == NAME::CASTING    )
    {
        if(history->type == NAME::IDENTIFIER && history->isFunID == true ||
           history->type == NAME::IO_SYSTEM && history->isFunID == true  ||
           history->type == NAME::CASTING && history->isFunID == true    )
        {
            if(this->ExpressionCheckOpenParam(token)) return nullptr;
            this->ThrowError("expected '(' after the function identifier.", token->startPos + 1);
        }

        if(token->value == ARITHMETIC::ADD ||
           token->value == ARITHMETIC::SUB ||
           token->value == ARITHMETIC::DIV ||
           token->value == ARITHMETIC::MUL ||
           token->value == ARITHMETIC::MOD ||
           token->value == ARITHMETIC::AND ||
           token->value == ARITHMETIC::OR  ||
           token->value == ARITHMETIC::SHIFTLEFT  ||
           token->value == ARITHMETIC::SHIFTRIGHT ||
           token->value == COMPARISON::DIFF       || 
           token->value == COMPARISON::EQUALS     || 
           token->value == COMPARISON::GREAT      || 
           token->value == COMPARISON::LESS       || 
           token->value == COMPARISON::GREATEQ    || 
           token->value == COMPARISON::LESSEQ     )
        {
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = token;

            return nullptr;
        }
    
        if(this->ExpressionCheckCloseParam(token)) return nullptr;
    
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
       history->value == ARITHMETIC::SHIFTRIGHT ||
       history->value == COMPARISON::DIFF       || 
       history->value == COMPARISON::EQUALS     || 
       history->value == COMPARISON::GREAT      || 
       history->value == COMPARISON::LESS       || 
       history->value == COMPARISON::GREATEQ    || 
       history->value == COMPARISON::LESSEQ     )
    {
        if(this->ExpressionCheckIdentifier(token)) return nullptr;
        if(this->ExpressionCheckType(token)) return nullptr;
        if(this->ExpressionCheckOpenParam(token)) return nullptr;
        
        if(!this->expressionFunctionStack->IsEmpty())
        {
            if(this->ExpressionCheckCloseParam(token)) return nullptr;
        } 
    }

    this->ThrowError(token);
    return nullptr;
}

bool Parser::ExpressionCheckCloseParam(Token* token)
{
    if(token->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        this->history = token;
        this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
        this->RemoveParemCounter();
        return true;
    }

    return false;
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
    if(token->type == NAME::NUMBER  ||
       token->type == NAME::BOOLEAN ||
       token->type == NAME::CHAR    ||
       token->type == NAME::TEXT    )
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
    if(token->type == NAME::IDENTIFIER ||
       token->type == NAME::IO_SYSTEM  ||
       token->type == NAME::CASTING    )
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
               this->ThrowError("Cannot implicitly convert type '" + getEntity->typeValue + "' to '" + this->ExpressionExpectedType + "' | ( " + token->value + " )", token->startPos + 1);
        }
        else if(this->IDFunTable->ExistIdentifier(token->value))
        {
            auto getEntity = this->IDFunTable->FindObjectIdentifier(token->value);

            if(getEntity == nullptr)
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Object not found in IDFunTable");
                exit(EXIT_FAILURE);
            }

            if(this->ExpressionExpectedType != EXPECTED_TYPE::TUNDEFINED && getEntity->type != this->ExpressionExpectedType)
               this->ThrowError("Cannot implicitly convert type '" + getEntity->type + "' to '" + this->ExpressionExpectedType + "' | ( " + token->value + " )", token->startPos + 1);

            token->isFunID = true;

            this->IncrementExpressionCommaCounter(getEntity->paramList.size());

            auto stackItem = this->BuildCallStackModel(token->value, getEntity->paramList[0].first, 0, 0);
            this->expressionFunctionStack->Insert(stackItem);
            this->expressionFunctionStack->ExpectedTypeHistory = this->ExpressionExpectedType;
            this->ExpressionExpectedType = getEntity->paramList[0].first;
        }
        else if(token->type == NAME::IO_SYSTEM ||
                token->type == NAME::CASTING   )
        {
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
    this->ExpressionDoOnce       = false;
}

void Parser::IncrementExpressionCommaCounter(int value)
{
    value--;
    this->ExpressionCommaCounter += value;
}

void Parser::DecrementExpressionCommaCounter()
{
    this->ExpressionCommaCounter--;

    if(!this->expressionFunctionStack->IsEmpty())
    {
        auto entity = this->expressionFunctionStack->GetCurrentItem();

        if(entity != nullptr)
        {
            entity->param_id++;
            auto funAttr = this->IDFunTable->FindObjectIdentifier(entity->ID);

            if(funAttr != nullptr)
            {
                entity->type = funAttr->paramList[entity->param_id].first;
                this->ExpressionExpectedType = entity->type;
            }
            else
                Output::PrintCustomizeError("Compiler internal error: ", "function no found in 'expression comma counter'");
        }
    }
}

CallStackModel* Parser::BuildCallStackModel(std::string ID, std::string type, int param_id, int parem_counter = 0)
{
    auto build = new CallStackModel(ID, type, param_id, parem_counter);
    return build;
}
