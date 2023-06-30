#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->buildingNode  = nullptr;
    this->history       = nullptr;
    this->ArithmeticBuildingNode = nullptr;
    this->buffer        = nullptr;
    
    this->tool    = new Tools();
    this->IDTable = new IDDeclarationStorage();
    this->codegen = new CodeGenerator(this->IDTable);
}

Parser::~Parser(){}

void Parser::Parse()
{
    while(true)
    {
        auto token = this->lexer->GetNextToken();

        if(token == nullptr) break;

        // Output::PrintDebug(token->type + " | " + token->value);

        switch(this->currentBranch)
        {
            case BRANCH_IDENTIFIER::UNDEFINED:
                this->IdentifyOperationType(token);
            break;

            case BRANCH_IDENTIFIER::VARIABLE_DECLARATION:
                this->VariableDeclaration(token);
            break;

            case BRANCH_IDENTIFIER::ARITHMETIC_OPERATION:
                this->ArithmeticOperation(token);
            break;
        }
    }

    // # Debug
    for(auto debug : this->ast)
    {
        std::cout << "Debug Branch Name: " << debug.first << "\n\n";
        this->tool->PrintParseTree(debug.second);
    }

    // # Generate Target Code
    this->codegen->Generate(this->ast);
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
    this->oldOperation  = branchName;
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
        node->parent = lastNode;

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

void Parser::ThrowError(Token* token)
{
    Output::PrintCustomizeError("Syntax Error: ", "Line: " + std::to_string(this->lexer->GetLineCounter()) + ":" + std::to_string(token->startPos) +" | unexpected token '" +token->value + "'");
    exit(EXIT_FAILURE);
}

void Parser::InsertAstNode(std::string branchName, AstNode* node)
{
    this->ast.push_back(std::make_pair(branchName, node));
}

void Parser::ResetState()
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->oldOperation  = BRANCH_IDENTIFIER::UNDEFINED;
    this->expectedType  = EXPECTED_TYPE::TUNDEFINED;
    this->history       = nullptr;
    this->buildingNode  = nullptr;
    this->precedence    = 0;
    this->isConstant    = false;
}

void Parser::AddParemCounter()
{
    this->paremCounter++;
    this->precedence++;
}

void Parser::RemoveParemCounter()
{
    this->paremCounter--;
    this->precedence--;
}












