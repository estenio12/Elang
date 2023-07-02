#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->buildingNode  = nullptr;
    this->history       = nullptr;
    this->ArithmeticBuildingNode = nullptr;
    
    this->tool       = new Tools();
    this->IDTable    = new IDDeclarationStorage();
    this->IDFunTable = new IDFunctionDeclarationStorage();
    this->codegen    = new CodeGenerator(this->IDTable);
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

            case BRANCH_IDENTIFIER::FUNCTION_DECLARATION:
                this->FunctionDeclaration(token);
            break;

            case BRANCH_IDENTIFIER::BUILD_PARAMETER_LIST:
                this->BuildParameterList(token);
            break;
        }
    }

    // # Debug
    // for(auto debug : this->ast)
    // {
    //     std::cout << "Debug Branch Name: " << debug.first << "\n\n";
    //     this->tool->PrintParseTree(debug.second);
    // }

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

    // # FUNCTION DECLARATION
    if(token->value == KEYWORDS::TFUN)
    {
        this->AssignCurrentBranch(BRANCH_IDENTIFIER::FUNCTION_DECLARATION);
        this->FunctionDeclaration(token);
    }
}

void Parser::AssignCurrentBranch(uint8_t branchName)
{
    this->currentBranch = branchName;
    this->observer  = branchName;
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
    this->observer      = BRANCH_IDENTIFIER::UNDEFINED;
    this->expectedType  = EXPECTED_TYPE::TUNDEFINED;
    this->history       = nullptr;
    this->buildingNode  = nullptr;
    this->isConstant    = false;
}

void Parser::AddParemCounter()
{
    this->ArithmeticParemCounter++;
}

void Parser::RemoveParemCounter()
{
    this->ArithmeticParemCounter--;
}

void Parser::AddDeepCounter()
{
    this->currentDeep++;
}

void Parser::RemoveDeepCounter()
{
    this->currentDeep--;
}

std::string Parser::GetExpectedType(Token* token)
{
    if(token->value == TYPE::NAME[TYPE::TBOOL]) return EXPECTED_TYPE::TBOOLEAN;
    if(token->value == TYPE::NAME[TYPE::TCHAR]) return EXPECTED_TYPE::TCHARACTER;
    if(token->value == TYPE::NAME[TYPE::TNUMBER]) return EXPECTED_TYPE::TNUMBER;
    if(token->value == TYPE::NAME[TYPE::TTEXT]) return EXPECTED_TYPE::TSTRING;
    if(token->value == TYPE::NAME[TYPE::TVOID]) return EXPECTED_TYPE::TVOID;

    Output::PrintCustomizeError("Compiler internal error: ", "No match type in variable declaration");
    exit(EXIT_FAILURE);
}

















