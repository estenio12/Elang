#include "../Include/Parser.hpp"

std::vector<std::pair<std::string, AstNode*>> Parser::Statement(Token* token)
{
    if(this->StatementState == BRANCH_IDENTIFIER::RETURN_EXPRESSION)
    {
        auto result = this->Expression(token, this->currentFunctionType);

        if(result != nullptr)
        {
            this->StatementState = BRANCH_IDENTIFIER::UNDEFINED;
            this->StatementList.push_back(std::make_pair(BRANCH_NAME::RETURN_EXPRESSION, result));
            this->ResetExpressionBuildingNode();
            this->history = nullptr;
        }

        return ReturnEmptyStatementList;
    }

    if(this->StatementState == BRANCH_IDENTIFIER::VARIABLE_DECLARATION)
    {
        auto result = this->VariableDeclaration(token);

        if(result != nullptr)
        {
            this->StatementState = BRANCH_IDENTIFIER::UNDEFINED;
            this->StatementList.push_back(std::make_pair(BRANCH_NAME::VARIABLE_DECLARATION, result));
            this->ResetVariableDeclarationBuildingNode();
            this->history = nullptr;
        }

        return ReturnEmptyStatementList;
    }

    if(this->StatementState == BRANCH_IDENTIFIER::ASSIGNMENT)
    {
        auto result = this->Assignment(token);

        if(result != nullptr)
        {
            this->StatementState = BRANCH_IDENTIFIER::UNDEFINED;
            this->StatementList.push_back(std::make_pair(BRANCH_NAME::ASSIGNMENT_EXPRESSION, result));
            this->ResetAssignmentBuildNode();
            this->history = nullptr;
        }

        return ReturnEmptyStatementList;
    }

    if(history == nullptr ||
       history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value == KEYWORDS::TRETURN)
        {
            this->StatementState = BRANCH_IDENTIFIER::RETURN_EXPRESSION;
            this->InsertExpressionNode(token, AST_DIRECTION::RIGHT);
            this->history = nullptr;
            return ReturnEmptyStatementList;         
        }

        if(token->value == KEYWORDS::TVAR   ||
           token->value == KEYWORDS::TCONST )
        {
            this->StatementState = BRANCH_IDENTIFIER::VARIABLE_DECLARATION;
            this->history = nullptr;
            this->Statement(token);
            return ReturnEmptyStatementList;         
        }
        
        if(token->value == KEYWORDS::TEND)
        {
            this->InsertStatementNode(token, AST_DIRECTION::RIGHT);
            this->RemoveDeepCounter();
            this->history = nullptr;
            return this->StatementList;
        }
        
        if(token->type == NAME::IDENTIFIER)
        {
            this->StatementState = BRANCH_IDENTIFIER::ASSIGNMENT;
            this->history = nullptr;
            this->Statement(token);
            return ReturnEmptyStatementList;      
        }

        this->ThrowError(token);
    }

    this->ThrowError(token);
    return ReturnEmptyStatementList;
}

void Parser::InsertStatementNode(Token* token, int direction)
{
    auto node = new AstNode(token);
    this->StatementList.push_back(std::make_pair(BRANCH_NAME::END_STATEMENT, node));
}

void Parser::ResetStatementList()
{
    this->StatementList.clear();
}

