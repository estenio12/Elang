#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->signatureMainBranch = BRANCH_IDENTIFIER::UNDEFINED;
}

Parser::~Parser(){}

void Parser::Parse()
{
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

        switch(this->currentBranch)
        {
            case BRANCH_IDENTIFIER::UNDEFINED:
                this->IdentifyOperationType(token);
            break;

            case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
                this->VariableDeclaration(token);
            break;

            case BRANCH_IDENTIFIER::OPERATION:
                this->ArithmeticOperation(token);
            break;
        }
    }
}

void Parser::IdentifyOperationType(Token* token)
{
    // # VARIABLE DECLARATION
    if(token->value == KEYWORDS::TVAR   ||
       token->value == KEYWORDS::TCONST)
    {
        this->AssignCurrentBranch(BRANCH_IDENTIFIER::VARIABLE_DECLARATION);
        this->VariableDeclaration(token);
    }
}

void Parser::AssignCurrentBranch(uint8_t branchName)
{
    this->currentBranch = branchName;
    this->signatureMainBranch = branchName;
}

void Parser::InsertBuildingNode(Token* token, uint8_t direction = 0)
{
    auto node = new AstNode(token);

    if(this->buildingNode == nullptr)
    {
        this->buildingNode = node;
        this->history = token;
    }
    else
    {
        auto lastNode = this->FindLastNode(buildingNode, direction);

        if(direction == AST_DIRECTION::LEFT)
           lastNode->left = node;
        else
           lastNode->right = node;
    }
}

AstNode* Parser::FindLastNode(AstNode* node, uint8_t direction)
{
    if(node == nullptr) return nullptr;

    if(direction == AST_DIRECTION::LEFT)
    {
        if(node->HasLeftNode())
           return this->FindLastNode(node->left, direction);
    
        return node;
    }
    else
    {
        if(node->HasRightNode())
           return this->FindLastNode(node->right, direction);
    
        return node;
    }
}

void Parser::ThrowError(std::string msg, int position = 0)
{
    Output::PrintCustomizeError("Syntax Error: ", "Line: " + std::to_string(this->lexer->GetLineCounter()) + ":" + std::to_string(position) +" | " + msg);
    exit(EXIT_FAILURE);
}

void Parser::InsertAstNode(std::string branchName, AstNode* node)
{
    this->ast.push_back(std::make_pair(branchName, node));
}

void Parser::ResetState()
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->history       = nullptr;
    this->buildingNode  = nullptr;
}

void Parser::InsertBuffer(Token* token)
{
    this->buffer.push(token);
}

Token* Parser::ConsumeNextTokenFromBuffer()
{
    auto token = this->buffer.top();
    this->buffer.pop();
    return token;
}











