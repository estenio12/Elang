#include "../Include/Parser.hpp"

AstNode* Parser::ConditionDeclaration(Token* token)
{   
    if(this->ConditionState == BRANCH_IDENTIFIER::EXPRESSION)
    {
        if(this->ConditionTypeExpression.empty() && token->value[0] != DELIMITERS::OPEN_PARAM)
        {
           this->ConditionTypeExpression = this->GetExpectedTypeByType(token);
           this->ExpressionDoOnce = false;
        }

        if(token->value[0] == DELIMITERS::OPEN_PARAM)
           this->ConditionOpenParam();
        
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
           this->ConditionCloseParam();
        
        auto result = this->Expression(token, this->ConditionTypeExpression);

        if(result != nullptr || this->ConditionParamCounter == 0)
        {
            if(this->ConditionParamCounter == 0)
               result = this->ExpressionBuildingNode;

            auto node = this->FindLastNode(this->ConditionBuildNode, AST_DIRECTION::RIGHT);

            if(node != nullptr)
               node->right = result;
            else
               Output::PrintCustomizeError("Compiler internal error: ", "Condition declaration empty tree");

            this->history = nullptr;
            this->AddConditionStmtCounter();
            this->ResetExpressionBuildingNode();
            return this->ConditionBuildNode;
        }

        return nullptr;
    }

    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TIF    ||
           token->value == KEYWORDS::TWHILE )
        {
            this->InsertConditionBuildNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }

        if(token->value == KEYWORDS::TELSE)
        {
            this->InsertConditionBuildNode(token, AST_DIRECTION::RIGHT);
            this->history = nullptr;
            return new AstNode(token);
        }

        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TIF    ||
       history->value == KEYWORDS::TWHILE )
    {
        if(token->value[0] == DELIMITERS::OPEN_PARAM)
        {
            this->ConditionState = BRANCH_IDENTIFIER::EXPRESSION;
            this->history = token;
            return this->ConditionDeclaration(token);
        }

        this->ThrowError(token);
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::InsertConditionBuildNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(ConditionBuildNode == nullptr)
    {
        ConditionBuildNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(ConditionBuildNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetConditionBuildNode()
{
    this->ConditionBuildNode = nullptr;
    this->ConditionTypeExpression.clear();
    this->ConditionState = BRANCH_IDENTIFIER::UNDEFINED;
}

void Parser::ConditionOpenParam()
{
    this->ConditionParamCounter++;
}

void Parser::ConditionCloseParam()
{
    this->ConditionParamCounter--;

    if(this->ConditionParamCounter < 0)
       Output::PrintCustomizeError("Syntax error: " + std::to_string(this->lexer->GetLineCounter()), "The parameter open but never close.");
}

void Parser::AddConditionStmtCounter()
{
    this->ConditionStmtCounter++;
    this->AddDeepCounter();
}

void Parser::RemoveConditionStmtCounter()
{
    this->ConditionStmtCounter--;
    this->RemoveDeepCounter();
}









