#include "../Include/Parser.hpp"

bool Parser::ArithmeticOperation(Token* token)
{
    if(history->value[0] == DELIMITERS::CLOSE_PARAM || 
       history->type == NAME::IDENTIFIER ||
       history->type == NAME::NUMBER ||
       history->type == NAME::BOOLEAN ||
       history->type == NAME::CHARACTER ||
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
            // // # Push to list
            // auto BuildNode = this->FindLastNode(this->ArithmeticBuildingNode, AST_DIRECTION::RIGHT);

            // auto node = new AstNode(token, "", this->precedence, nullptr, nullptr, BuildNode);
            // auto nodeLeft = new AstNode(buffer, "", this->precedence, nullptr, nullptr, BuildNode);
            // node->left = nodeLeft;

            // // # Clear Buffer
            // buffer = nullptr;

            // if(BuildNode == nullptr)
            // {
            //     this->ArithmeticBuildingNode = node;
            // }
            // else
            // {
            //     BuildNode->right = node;
            // }

            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            this->history = token;

            return true;
        }
    
        if(token->value[0] == DELIMITERS::CLOSE_PARAM)
        {
            this->history = token;
            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            this->RemoveParemCounter();
            return true;
        }
    
        if(token->value[0] == DELIMITERS::EOL)
        {
            if(paremCounter > 0)
                this->ThrowError("The parentheses were opened, but never closed.", token->startPos);

            if(paremCounter < 0)
                this->ThrowError("The parentheses were closed, but never opened.", token->startPos);

            // this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            // this->ArithmeticCommit();
            // return true;
        // }
            auto lastNode = this->FindLastNode(buildingNode, AST_DIRECTION::RIGHT);

            if(this->buffer != nullptr)
            {
                int precedence = (history->value[0] == DELIMITERS::CLOSE_PARAM) ? this->precedence + 1 : this->precedence; 
                auto lastNodeArithmentic = this->FindLastNode(this->ArithmeticBuildingNode, AST_DIRECTION::RIGHT);
                auto node = new AstNode(this->buffer, "", precedence, nullptr, nullptr, lastNodeArithmentic);

                if(lastNodeArithmentic == nullptr)
                    this->ArithmeticBuildingNode = node;
                else
                    lastNodeArithmentic->right = node;
            }
           
            // # Insert EOL token into tree
            this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
            
            if(lastNode == nullptr)
            {
                lastNode = this->ArithmeticBuildingNode;
                this->ArithmeticBuildingNode = nullptr;
                this->ArithmeticCommit();
                return true;
            }
            else
            {
                lastNode->right = this->ArithmeticBuildingNode;
                this->ArithmeticBuildingNode = nullptr;
                this->ArithmeticCommit();
                return true;
            }

            this->ThrowError(token);
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
        if(this->ArithmeticOperationCheckIdentifier(token)) return true;
        if(this->ArithmeticOperationCheckType(token)) return true;
        if(this->ArithmeticOperationCheckOpenParam(token)) return true;
    }

    this->ThrowError(token);

    return false;
}

void Parser::ArithmeticCommit()
{
    if(this->buildingNode != nullptr)
    {
        // std::string build;
        // for(auto item : this->ArithmeticStack) build += item;

        switch(this->oldOperation)
        {
            case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
                // auto node = new AstNode(new Token(build, NAME::EXPRESSION));
                // this->InsertBuildingNode(new Token(build, NAME::EXPRESSION), AST_DIRECTION::RIGHT);
                this->VariableDeclarationCommit();
            break;
            
            default:
                this->InsertAstNode(BRANCH_NAME::ARITHMETIC_OPERATION, this->ArithmeticBuildingNode);
                // auto node = new AstNode(new Token(build, NAME::EXPRESSION));
                // this->ast.push_back(std::make_pair(BRANCH_NAME::ARITHMETIC_OPERATION, node));
                // this->ArithmeticStack.clear();
                this->ResetState();
            break;
        }
    }
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
    if(token->type == NAME::NUMBER ||
       token->type == NAME::BOOLEAN ||
       token->type == NAME::CHARACTER ||
       token->type == NAME::STRING)
    {
        if(token->type != this->expectedType)
            this->ThrowError("Cannot implicitly convert type '" + token->type + "' to '" + this->expectedType + "'", token->startPos + 1);

        // this->buffer  = token;
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
        if(!this->IDTable->ExistIdentifier(token->value))
            this->ThrowError("Variable not declared in scope '" + token->value + "'", token->startPos + 1);

        auto getEntity = this->IDTable->FindObjectIdentifier(token->value);

        if(getEntity == nullptr)
        {
            Output::PrintCustomizeError("Compiler internal error: ", "Object not found in IDTable");
            exit(EXIT_FAILURE);
        }

        if(getEntity->typeValue != this->expectedType)
           this->ThrowError("Cannot implicitly convert type '" + getEntity->typeValue + "' to '" + this->expectedType + "'", token->startPos + 1);

        // this->buffer  = token;
        this->InsertArithmeticNode(token, AST_DIRECTION::RIGHT);
        this->history = token;
        return true;
    }

    return false;
}

void Parser::InsertArithmeticNode(Token* token, int direction)
{
    // this->ArithmeticStack.push_back(token->value);
    auto node = new AstNode(token);

    if(this->ArithmeticBuildingNode == nullptr)
    {
        this->ArithmeticBuildingNode = node;
        this->history = token;
    }
    else
    {
        auto lastNode = this->FindLastNode(ArithmeticBuildingNode, direction);

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}












