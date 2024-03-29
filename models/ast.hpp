// #######################################
// ## 
// ## @author: Estenio Garcia
// ## @copyright: (c) Allright reserved 
// ## @License: Apache 2.0
// ## 
// #######################################

#pragma once

#include <vector>
#include "../models/token.hpp"
#include "../helpers/mem-tools.hpp"
#include "../headers/output.hpp"
#include "block-stmt-policy.hpp"

using CallFunDictionary = std::vector<std::pair<std::string, class AstBranch*>>;

enum EBRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION,
    FUNCTION_DECLARATION,
    CALL_FUNCTION,
    RETURN_EXPRESSION,
    ASSIGNMENT,
    BLOCK_STATEMENT,
    BREAK_EXPRESSION,
    WHILE_DECLARATION,
    IF_ELSE_CONDITION
};

class AstNode
{
    public:
        EBRANCH_TYPE kind = EBRANCH_TYPE::UNDEFINED;

    public:
        AstNode(){}
        ~AstNode(){}

    public:
        virtual std::string GetInterface() { return ""; }
        virtual std::string GetByteCode() = 0;
};

class AstBranch
{
    public:
        AstNode* entity;
        bool IsGlobalScope = false;

    public:
        AstBranch(AstNode* entity, bool IsGlobalScope = false):entity(entity), IsGlobalScope(IsGlobalScope){}
        ~AstBranch()
        {
            MemTools::FreeObjectFromMemory(entity);
        }
};

class Ast
{
    public:
        std::vector<AstBranch*> tree;

    public:
        Ast(){}
        ~Ast()
        {
            MemTools::FreeVectorFromMemory(tree);
        }

    public:
        void AddNode(AstBranch* branch) { this->tree.push_back(branch); }
        AstBranch* ConsumeBranch() 
        { 
            if(tree.size() > 0)
            {
                auto tmpBranch = tree[0];
                tree.erase(tree.begin(), tree.begin() + 1);
                return tmpBranch;
            }

            return nullptr;
        }
        bool HasContent() { return this->tree.size() > 0; }
};

class BinaryOperation
{
    public:
        bool IsCallFuncion = false;

    public:
        Token* token;
        BinaryOperation* left;
        BinaryOperation* right;
        class CallFunction* call_function;

    public:
        BinaryOperation(BinaryOperation* left, Token* token, BinaryOperation* right):
        token(token), left(left), right(right){}
        ~BinaryOperation(){}
};

class Expression : public AstNode
{
    public:
        std::vector<Token*> TokenVector;

    public:
        Expression(){ kind = EBRANCH_TYPE::EXPRESSION; }

        ~Expression()
        {
            MemTools::FreeVectorFromMemory(TokenVector);
        }

    public:
        std::string GetByteCode() override 
        { 
            // # Get output code
            std::string buffer;

            for(auto item : this->TokenVector)
                buffer += item->value;

            return buffer;
        }
};

class VariableDeclaration : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::string scopeName = "GLOBAL";
        int deep = 0;
        bool isConstant = false;
        bool isArray    = false;
        Expression* expression = nullptr;

    public:
        VariableDeclaration(){ kind = EBRANCH_TYPE::VARIABLE_DECLARATION; }

        VariableDeclaration(VariableDeclaration* origin)
        {
            kind = EBRANCH_TYPE::VARIABLE_DECLARATION;
            operator=(origin);
        }

        ~VariableDeclaration()
        {
            delete expression;
        }

    public:
        bool IsInitialized(){ return this->expression != nullptr; }
        bool IsGlobalScope(){ return this->scopeName == "GLOBAL"; }

        VariableDeclaration* operator=(const VariableDeclaration* origin)
        {
            if(this != origin)
            {
                this->name       = origin->name;
                this->type       = origin->type;
                this->scopeName  = origin->scopeName;
                this->deep       = origin->deep;
                this->isConstant = origin->isConstant;
                this->isArray    = origin->isArray;
                this->expression = origin->expression;
            }

            return this;
        }

    public:
        std::string GetByteCode() override 
        { 
            // # result
            std::string outcode;

            // # Check if it const variable
            if(isConstant) outcode = "const ";

            // # Build type varaible
            outcode += this->GetType();

            // # Set add variable name
            outcode += this->name;

            // # Check if it has initializer
            if(expression != nullptr)
                outcode += "=" + this->expression->GetByteCode();

            // # Close variable declaration
            outcode.push_back(';');

            return outcode; 
        }

    private:
        std::string GetType()
        {
            if(this->type == TYPE::T_BOOL)   return TYPE::T_BOOL + " ";
            if(this->type == TYPE::T_CHAR)   return TYPE::T_CHAR + " ";
            if(this->type == TYPE::T_FLOAT)  return TYPE::T_FLOAT + " ";
            if(this->type == TYPE::T_INT)    return TYPE::T_INT + " ";
            if(this->type == TYPE::T_STRING) return "std::" + TYPE::T_STRING + " ";
            if(this->type == TYPE::T_VOID)   return TYPE::T_VOID + " ";

            Output::PrintCustomizeError("Fatal Error: ", "In code generator variable declartion has not type.");
            exit(EXIT_FAILURE);
        }
};

class CallFunction : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::vector<Expression*> ArgumetList;

    public:
        CallFunction(){ this->kind = EBRANCH_TYPE::CALL_FUNCTION; }
        ~CallFunction(){ MemTools::FreeVectorFromMemory(ArgumetList); }
    
    public:
        void InsertArgument(Expression* expr)
        {
            this->ArgumetList.push_back(expr);
        }
    
    public:
        std::string GetByteCode() override 
        { 
            std::string outcode;

            // # Function name
            outcode += this->name;

            outcode.push_back('(');

            // # Get Arguments of call function
            for(int i = 0; i < ArgumetList.size(); i++)
            {
                if(i > 0)
                    outcode.push_back(',');

                outcode += ArgumetList[i]->GetByteCode();
            }

            outcode.push_back(')');

            return outcode; 
        }

};

class ReturnExpression : public AstNode
{
    public:
        Expression* expression;

    public:
        ReturnExpression(){this->kind = RETURN_EXPRESSION;}
        ~ReturnExpression()
        {
            delete expression;
        }

    public:
        std::string GetByteCode() override 
        { 
            return "return " + this->expression->GetByteCode() + ";";
        }
};

class ParameterDeclaration
{
    public:
        std::string name;
        std::string type;

    public:
        ParameterDeclaration(){}
        ~ParameterDeclaration(){}
};

class BlockStatement : public AstNode
{
    public:
        std::string GlobalType;
        bool closeWithElse = false;
    public:
        std::vector<AstBranch*> content;

    public:
        BlockStatement(std::string type): GlobalType(type)
        {
            this->kind = EBRANCH_TYPE::BLOCK_STATEMENT;
        }

        ~BlockStatement(){}

    public:
        bool HasEntity(EBRANCH_TYPE entity)
        {
            for(auto item : content)
            {
                if(item->entity->kind == entity)
                    return true;
            }

            return false;
        }

    public:
        std::string GetByteCode() override
        {
            std::string outcode;

            for(auto item : this->content)
            {
                outcode += item->entity->GetByteCode();
                if(item->entity->kind == EBRANCH_TYPE::CALL_FUNCTION)
                    outcode.push_back(';');
            }

            return outcode;
        }
};

class FunctionDeclaration : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::vector<ParameterDeclaration*> parameterList;

    public:
        BlockStatement* block_stmt;

    private:
        const std::string STANDARD_PROGRAM_NAME = "__elang_class_runnable_cxx::";

    public:
        FunctionDeclaration()
        {
            this->kind = EBRANCH_TYPE::FUNCTION_DECLARATION;
        }

        ~FunctionDeclaration()
        {
            MemTools::FreeVectorFromMemory(parameterList);
            MemTools::FreeObjectFromMemory(block_stmt);
        }

    public:
        bool ExistsParameter(std::string name)
        {
            for(auto item : parameterList)
                if(item->name == name) return true;
            
            return false;
        }

        ParameterDeclaration* GetParameterByName(std::string name)
        {
            for(auto item : parameterList) 
                if(item->name == name) return item;

            return nullptr;
        }

    public:
        std::string GetByteCode() override 
        { 
            std::string outcode;

            // # Set type function
            if(this->type == TYPE::T_STRING)
                outcode += "std::string ";
            else
                outcode += this->type + " ";

            // # Set template 
            outcode += this->STANDARD_PROGRAM_NAME;

            // # Set function name
            outcode += this->name;

            // # Set parameters
            outcode.push_back('(');

            for(int i = 0; i < parameterList.size(); i++)
            {
                if(i > 0) outcode.push_back(',');
                
                if(parameterList[i]->type == TYPE::T_STRING)
                    outcode += "std::string ";
                else
                    outcode += parameterList[i]->type + " ";

                outcode += parameterList[i]->name;
            }

            // # Set close parenthesis
            outcode.push_back(')');

            // # Open function scope
            outcode.push_back('{');

            outcode += this->block_stmt->GetByteCode();

            // # Close function scope 
            outcode += "}\n";

            return outcode; 
        }

        std::string GetInterface() override
        {
            std::string outcode;

            // # Set type function
            if(this->type == TYPE::T_STRING)
                outcode += "std::string ";
            else
                outcode += this->type + " ";

            // # Set function name
            outcode += this->name;

            // # Set open parenthesis
            outcode.push_back('(');

            // # Set parameters
            for(int i = 0; i < this->parameterList.size(); i++)
            {
                if(i > 0) outcode.push_back(',');
                
                if(parameterList[i]->type == TYPE::T_STRING)
                    outcode += "std::string ";
                else
                    outcode += parameterList[i]->type + " ";

                outcode += this->parameterList[i]->name;
            }

            // # Set close parenthesis
            outcode.push_back(')');

            // # Close interface
            outcode.push_back(';');

            return outcode;
        }
};

class Assignment: public AstNode
{
    public:
        std::string name;
        Expression* expression = nullptr;

    public:
        Assignment()
        {
            this->kind = EBRANCH_TYPE::ASSIGNMENT;
        }
        ~Assignment(){}

    public:
        std::string GetByteCode() override 
        {
            // # result
            std::string outcode;

            // # Set add variable name
            outcode += this->name;

            // # Check if it has initializer
            if(expression != nullptr)
                outcode += "=" + this->expression->GetByteCode();

            // # Close variable declaration
            outcode.push_back(';');

            return outcode; 
        }

};

class BreakStatement : public AstNode
{
    public:
        BreakStatement(){ this->kind = EBRANCH_TYPE::BREAK_EXPRESSION; }
        ~BreakStatement(){}

    public:
        std::string GetByteCode() override
        {
            return "break;";
        }
};

class WhileDeclaration : public AstNode
{
    public:
        Expression* condition;
        BlockStatement* block_stmt;

    public:
        WhileDeclaration(){ this->kind = EBRANCH_TYPE::WHILE_DECLARATION; }
        ~WhileDeclaration()
        { 
            MemTools::FreeObjectFromMemory(condition); 
            MemTools::FreeObjectFromMemory(block_stmt); 
        }
    
    public:
        std::string GetByteCode() override 
        { 
            std::string outcode;

            outcode += "while(";

            outcode += condition->GetByteCode();

            outcode += "){";

            outcode += block_stmt->GetByteCode();

            outcode.push_back('}');

            return outcode; 
        }
};

class IfElseCondition : public AstNode
{
    public:
        Expression* condition;
        BlockStatement* if_block_stmt   = nullptr;
        BlockStatement* else_block_stmt = nullptr;

    public:
        IfElseCondition(){ this->kind = EBRANCH_TYPE::IF_ELSE_CONDITION; }
        ~IfElseCondition()
        { 
            MemTools::FreeObjectFromMemory(condition); 
            MemTools::FreeObjectFromMemory(if_block_stmt); 
            MemTools::FreeObjectFromMemory(else_block_stmt); 
        }
    
    public:
        std::string GetByteCode() override 
        { 
            std::string outcode;

            outcode += "if(";

            outcode += condition->GetByteCode();

            outcode += "){";

            outcode += if_block_stmt->GetByteCode();

            outcode.push_back('}');

            if(this->else_block_stmt != nullptr)
            {
                outcode += "else{";

                outcode += else_block_stmt->GetByteCode();

                outcode.push_back('}');
            }

            return outcode; 
        }
};

