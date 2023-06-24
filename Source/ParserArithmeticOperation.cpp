#include "../Include/Parser.hpp"

bool Parser::ArithmeticOperation(Token* token)
{
    if(token->value[0] == DELIMITERS::EOL)
    {
        if(paremCounter > 0)
            this->ThrowError("The parentheses were opened, but never closed.", token->startPos);

        if(paremCounter < 0)
            this->ThrowError("The parentheses were closed, but never opened.", token->startPos);

        auto lastNode = this->FindLastNode(buildingNode, AST_DIRECTION::RIGHT);

        if(this->buffer != nullptr)
        {
            auto node = new AstNode(this->buffer, "", nullptr, nullptr);
            auto lastNodeArithmentic = this->FindLastNode(this->ArithmeticBuildingNode, AST_DIRECTION::RIGHT);

            lastNodeArithmentic->right = node;
        }
        
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

    if(history->value[0] == DELIMITERS::ASSIGN)
    {
        if(token->type == NAME::IDENTIFIER ||
           token->type == NAME::NUMBER)
        {
            this->buffer  = token;
            this->history = token;
            return true;
        }

        if(token->value[0] == DELIMITERS::OPEN_PARAM)
        {
            this->AddParemCounter();
            this->history = token;
            return true;
        }

        this->ThrowError(token);
    }

    if(history->value[0] == DELIMITERS::CLOSE_PARAM || 
       history->type == NAME::IDENTIFIER ||
       history->type == NAME::NUMBER)
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
            auto node = new AstNode(token, "", nullptr, nullptr);
            auto nodeLeft = new AstNode(buffer, "", nullptr, nullptr);
            node->left = nodeLeft;

            // # Clear Buffer
            buffer = nullptr;

            // # Push to list
            auto BuildNode = this->FindLastNode(this->ArithmeticBuildingNode, AST_DIRECTION::RIGHT);

            if(BuildNode == nullptr)
            {
                this->ArithmeticBuildingNode = node;
            }
            else
            {
                BuildNode->right = node;
            }

            this->history = token;

            return true;
        }
    }

    if(history->value == ARITHMETIC::ADD ||
       history->value == ARITHMETIC::SUB ||
       history->value == ARITHMETIC::DIV ||
       history->value == ARITHMETIC::MUL ||
       history->value == ARITHMETIC::MOD ||
       history->value == ARITHMETIC::AND ||
       history->value == ARITHMETIC::OR  ||
       history->value == ARITHMETIC::SHIFTLEFT  ||
       history->value == ARITHMETIC::SHIFTRIGHT )
    {
        if(token->type == NAME::IDENTIFIER ||
           token->type == NAME::NUMBER)
        {
            this->buffer  = token;
            this->history = token;
            return true;
        }
    }

    return false;
}

void Parser::ArithmeticCommit()
{
    if(this->buildingNode != nullptr)
    {
        switch (this->oldOperation)
        {
            case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
                this->VariableDeclarationCommit();
            break;
            
            default:
                this->InsertAstNode(BRANCH_NAME::ARITHMETIC_OPERATION, this->buildingNode);
                this->ResetState();
            break;
        }
    }
}