#include "../Include/Parser.hpp"

Parser::Parser(Lexer* lexer):lexer(lexer)
{
    this->currentBranch = BRANCH_IDENTIFIER::UNDEFINED;
    this->buildingNode  = nullptr;
    this->history       = nullptr;
    this->ExpressionBuildingNode = nullptr;
    
    this->tool       = new Tools();
    this->IDTable    = new IDDeclarationStorage();
    this->IDFunTable = new IDFunctionDeclarationStorage();
    this->codegen    = new CodeGenerator(this->IDTable);
    this->expressionFunctionStack = new CallStack();
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
                this->CommitEntity(BRANCH_NAME::VARIABLE_DECLARATION, this->VariableDeclaration(token));
            break;

            case BRANCH_IDENTIFIER::FUNCTION_DECLARATION:
                this->CommitEntity(BRANCH_NAME::FUNCTION_DECLARATION, this->FunctionDeclaration(token));
            break;

            case BRANCH_IDENTIFIER::ASSIGNMENT:
                this->CommitEntity(BRANCH_NAME::ASSIGNMENT_EXPRESSION, this->Assignment(token));
            break;

            case BRANCH_IDENTIFIER::CALL_FUNCTION:
                this->CommitEntity(BRANCH_NAME::CALL_FUNCTION, this->CallFunction(token));
            break;

            case BRANCH_IDENTIFIER::CONDITION_DECLARATION:
                this->CommitEntity(BRANCH_NAME::CONDITION_DECLARATION, this->ConditionDeclaration(token));
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

    // # FUNCTION DECLARATION
    if(token->value == KEYWORDS::TFUN)
    {
        this->AssignCurrentBranch(BRANCH_IDENTIFIER::FUNCTION_DECLARATION);
        this->FunctionDeclaration(token);
    }

    // # ID operation identifier
    if(token->type == NAME::IDENTIFIER)
    {
        auto typeID = this->IdentifyTypeID(token->value);

        switch(typeID)
        {
            case TYPE_ID::_VARIABLE_ASSIGNMENT:
                this->AssignCurrentBranch(BRANCH_IDENTIFIER::ASSIGNMENT);
                this->Assignment(token);
            break;

            case TYPE_ID::_CALL_FUNCTION:
                this->AssignCurrentBranch(BRANCH_IDENTIFIER::CALL_FUNCTION);
                this->CallFunction(token);
            break;
        
            default:
                this->ThrowError("Identifier not declared in scope '" + token->value + "'", token->startPos + 1);
            break;
        }
    }
    
    // # CONDITION DECLARATION
    if(token->value == KEYWORDS::TIF    ||
       token->value == KEYWORDS::TWHILE )
    {
        this->AssignCurrentBranch(BRANCH_IDENTIFIER::CONDITION_DECLARATION);
        this->ConditionDeclaration(token);
    }

    if(token->value == KEYWORDS::TELSE)
    {
        this->CommitEntity(BRANCH_NAME::CONDITION_DECLARATION, this->ConditionDeclaration(token));
    }

    // # CLOSE STATEMENT
    if(token->value == KEYWORDS::TEND)
    {
        this->CommitEntity(BRANCH_NAME::CLOSE_STATEMENT, this->CloseStatment(token));
    }
}

int Parser::IdentifyTypeID(std::string name)
{
    auto varId = this->IDTable->FindObjectIdentifier(name);
    if(varId != nullptr) return TYPE_ID::_VARIABLE_ASSIGNMENT;

    auto funId = this->IDFunTable->FindObjectIdentifier(name);
    if(funId != nullptr) return TYPE_ID::_CALL_FUNCTION;

    return TYPE_ID::_NONE;
}

void Parser::CommitEntity(std::string branch_name, AstNode* tree)
{
    if(tree != nullptr) 
    {
        this->InsertAstNode(branch_name, tree);
        this->ResetState();
    }
}

void Parser::AssignCurrentBranch(uint8_t branchName)
{
    this->currentBranch = branchName;
    this->observer  = branchName;
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
    this->expectedType  = EXPECTED_TYPE::TUNDEFINED;
    this->history       = nullptr;
    this->isConstant    = false;

    // # Reset great entities
    this->VariableDeclarationBuildingNode = nullptr;
    this->FunctionDeclarationBuildingNode = nullptr;
    this->AssignmentBuildingNode          = nullptr;
    this->ResetCallFunctionBuildNode();
    this->ResetConditionBuildNode();
}

void Parser::AddParemCounter()
{
    this->ExpressionParemCounter++;

    if(!this->expressionFunctionStack->IsEmpty())
    {
        auto entity = this->expressionFunctionStack->GetCurrentItem();
        if(entity != nullptr) entity->parem_counter++;
    }
}

void Parser::RemoveParemCounter()
{
    this->ExpressionParemCounter--;

    if(!this->expressionFunctionStack->IsEmpty())
    {
        auto entity = this->expressionFunctionStack->GetCurrentItem();

        if(entity != nullptr)
        {
            if(this->expressionFunctionStack->RemoveParemCounter())
            {
                this->ExpressionExpectedType = this->expressionFunctionStack->ExpectedTypeHistory;
            }
        }
    }
}

void Parser::AddDeepCounter()
{
    this->currentDeep++;
}

void Parser::RemoveDeepCounter()
{
    this->currentDeep--;
}

std::string Parser::GetExpectedTypeByValue(Token* token)
{
    if(token->value == TYPE::NAME[TYPE::TBOOL]) return EXPECTED_TYPE::TBOOLEAN;
    if(token->value == TYPE::NAME[TYPE::TCHAR]) return EXPECTED_TYPE::TCHARACTER;
    if(token->value == TYPE::NAME[TYPE::TNUMBER]) return EXPECTED_TYPE::TNUMBER;
    if(token->value == TYPE::NAME[TYPE::TTEXT]) return EXPECTED_TYPE::TTEXT;
    if(token->value == TYPE::NAME[TYPE::TVOID]) return EXPECTED_TYPE::TVOID;

    Output::PrintCustomizeError("Compiler internal error: ", "No match type in variable declaration");
    exit(EXIT_FAILURE);
}

std::string Parser::GetExpectedTypeByType(Token* token)
{
    if(token->type == TYPE::NAME[TYPE::TBOOL] || token->type == NAME::BOOLEAN) 
       return EXPECTED_TYPE::TBOOLEAN;

    if(token->type == TYPE::NAME[TYPE::TCHAR]) return EXPECTED_TYPE::TCHARACTER;
    if(token->type == TYPE::NAME[TYPE::TNUMBER]) return EXPECTED_TYPE::TNUMBER;
    if(token->type == TYPE::NAME[TYPE::TTEXT]) return EXPECTED_TYPE::TTEXT;
    if(token->type == TYPE::NAME[TYPE::TVOID]) return EXPECTED_TYPE::TVOID;

    if(token->type == NAME::IDENTIFIER)
    {
        auto result = this->GetExpectedTypeByID(token);
        if(result != EMPTY) return result; 
    }

    Output::PrintCustomizeError("Compiler internal error: ", "No match type in GetExpectedTypeByType | " + token->type + " | " + token->value);
    exit(EXIT_FAILURE);
}

std::string Parser::GetExpectedTypeByID(Token* token)
{
    auto varId = this->IDTable->FindObjectIdentifier(token->value);
    if(varId != nullptr) return varId->typeValue;

    auto funId = this->IDFunTable->FindObjectIdentifier(token->value);
    if(funId != nullptr) return funId->type;

    return EMPTY;
}















