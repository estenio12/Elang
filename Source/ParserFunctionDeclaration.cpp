#include "../Include/Parser.hpp"

AstNode* Parser::FunctionDeclaration(Token* token)
{
    if(this->FunctionDeclarationState == BRANCH_IDENTIFIER::FUNCTION_BODY)
    {
        auto result = this->FunctionBodyDeclaration(token);

        if(result != nullptr)
        {
            this->FunctionDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->FunctionDeclarationBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetFunctionDeclarationBodyBuildingNode();
                return this->FunctionDeclarationBuildingNode;
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Function declaration structure not found!");
            }
        }

        return nullptr;
    }

    if(this->FunctionDeclarationState == BRANCH_IDENTIFIER::BUILD_PARAMETER_LIST)
    {
        auto result = this->BuildParameterList(token);

        if(result != nullptr)
        {
            this->FunctionDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->FunctionDeclarationBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetParameterListBuildingNode();
                this->FunctionDeclarationState = BRANCH_IDENTIFIER::FUNCTION_BODY;
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Function declaration structure not found!");
            }
        }

        return nullptr;
    }

    if(history == nullptr)
    {
        if(token->value == KEYWORDS::TFUN)
        {
            this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->observer = BRANCH_IDENTIFIER::FUNCTION_DECLARATION; 
            this->history  = token;
            return nullptr;
        }

        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TFUN)
    {
        this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return nullptr;
    }

    if(history->value[0] == DELIMITERS::COLON)
    {
        if(token->value == NAME::NUMBER    ||
           token->value == NAME::STRING    ||
           token->value == NAME::CHARACTER ||
           token->value == NAME::TVOID     ||
           token->value == NAME::BOOLEAN   ||
           token->value == NAME::NUMBER    )
        {
            this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->currentFunctionType = this->GetExpectedType(token);
            return nullptr;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::TYPE)
    {
        if(token->type == NAME::IDENTIFIER)
        {
            if(this->IDTable->ExistIdentifier(token->value, this->currentScope, this->currentDeep) ||
               this->IDFunTable->ExistIdentifier(token->value))
               this->ThrowError("Duplicate identifier in function declaration '" +token->value+ "'" , token->startPos);
            
            auto tempID = this->IDFunTable->CreateRow(token->value, this->currentFunctionType);

            this->IDFunTable->InsertFunctionID(tempID);
            this->currentScope = token->value;
            this->history      = token;
            return nullptr;
        }

        this->ThrowError(token);
    }

    if(history->type == NAME::IDENTIFIER)
    {
        if(token->value[0] == DELIMITERS::OPEN_PARAM)
        {
            this->AddParemCounter();
            this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            this->FunctionDeclarationState = BRANCH_IDENTIFIER::BUILD_PARAMETER_LIST;
            
            return nullptr;
        }
        
        this->ThrowError(token);
    }

    if(history->value[0] == DELIMITERS::OPEN_PARAM)
    {
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->AddDeepCounter();
            this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }
    }

    if(history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value[0] == DELIMITERS::EOL)
        {
            this->RemoveDeepCounter();
            this->InsertFunctionDeclarationNode(token, AST_DIRECTION::RIGHT);
            this->FunctionDeclarationReset();
            this->history = token;
            return this->FunctionDeclarationBuildingNode;
        }
    }

    this->ThrowError(token);
    return nullptr;
}

void Parser::FunctionDeclarationReset()
{
    this->currentScope         = STANDARD_SCOPE_NAME::GLOBALSCOPE;
    this->currentFunctionType  = EXPECTED_TYPE::TUNDEFINED;
    this->FunctionDeclarationState = BRANCH_IDENTIFIER::UNDEFINED;
}

void Parser::InsertFunctionDeclarationNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(FunctionDeclarationBuildingNode == nullptr)
    {
        FunctionDeclarationBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(FunctionDeclarationBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::InsertFunctionDeclarationBodyNode(Token* token, int direction)
{
    auto node = new AstNode(token);

    if(FunctionDeclarationBodyBuildingNode == nullptr)
    {
        FunctionDeclarationBodyBuildingNode = node;
    }
    else
    {
        auto lastNode = this->FindLastNode(FunctionDeclarationBodyBuildingNode, direction);
        node->parent = lastNode;

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

void Parser::ResetFunctionDeclarationBodyBuildingNode()
{
    this->FunctionDeclarationBodyBuildingNode = nullptr;
}

AstNode* Parser::FunctionBodyDeclaration(Token* token)
{
    if(this->FunctionDeclarationBodyState == BRANCH_IDENTIFIER::ARITHMETIC_OPERATION)
    {
        auto result = this->ArithmeticOperation(token, this->currentFunctionType);

        if(result != nullptr)
        {
            this->FunctionDeclarationBodyState = BRANCH_IDENTIFIER::UNDEFINED;
            auto lastNode = this->FindLastNode(this->FunctionDeclarationBodyBuildingNode, AST_DIRECTION::RIGHT);
        
            if(lastNode != nullptr)
            {
                lastNode->right = result;
                this->ResetArithmeticBuildingNode();
            }
            else
            {
                Output::PrintCustomizeError("Compiler internal error: ", "Function declaration structure not found!");
            } 
        }

        return nullptr;
    }

    if(history->value[0] == DELIMITERS::CLOSE_PARAM)
    {
        if(token->value == KEYWORDS::TRETURN)
        {
            this->InsertFunctionDeclarationBodyNode(token, AST_DIRECTION::RIGHT);
            this->history = token;
            return nullptr;
        }
        
        this->ThrowError(token);
    }

    if(history->value == KEYWORDS::TRETURN)
    {

        this->FunctionDeclarationBodyState = BRANCH_IDENTIFIER::ARITHMETIC_OPERATION;
        this->history = token;
        return nullptr;
    }

    if(history->value[0] == DELIMITERS::EOL)
    {
        if(token->value == KEYWORDS::TEND)
        {
            this->RemoveDeepCounter();
            this->history = token;
            return this->FunctionDeclarationBodyBuildingNode;
        }
    }

    this->ThrowError(token);
    return nullptr;
}


