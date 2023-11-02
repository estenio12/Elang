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

using CallFunDictionary = std::vector<std::pair<std::string, class AstBranch*>>;

enum EBRANCH_TYPE
{
    UNDEFINED,
    VARIABLE_DECLARATION,
    EXPRESSION,
    FUNCTION_DECLARATION,
    CALL_FUNCTION,
    RETURN_EXPRESSION
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
        bool IsLiteralOperation = true;
        bool IsConcatenation    = false;
        bool TerminateWithCloseParenthesis = false;
        BinaryOperation* operation;
        CallFunDictionary CallTable;

    public:
        Expression(){ kind = EBRANCH_TYPE::EXPRESSION; }

        #pragma GCC diagnostic ignored "-Wdelete-incomplete"

        ~Expression()
        {
            MemTools::FreeObjectFromMemory(operation);
            
            for(auto item : CallTable)
                if(item.second != nullptr)
                    delete item.second;

            CallTable.clear();
        }

        #pragma GCC diagnostic pop

        bool ExistCallFunctionID(std::string ID)
        {
            for(auto item : CallTable)
                if(item.first == ID) return true;
            return false;
        }

    public:
        std::string GetByteCode() override 
        { 
            // # Get output code
            auto outcode = this->Visitor(this->operation);
            
            // # Free Binary operation from memory
            this->FreeBinaryOperationFromMemory(this->operation);
            
            // # Return output code
            return outcode;
        }

    private:
        std::string Visitor(BinaryOperation* oper)
        {
            if(oper != nullptr)
            {
                // # Return the simple value attribution 
                if(oper->left == nullptr && oper->right == nullptr)
                    return oper->token->value;

                // # Return expression
                if(oper->token->type == TYPE_TOKEN::T_ARITHMETIC)
                {
                    auto arithmeticOperator = oper->token->value; 

                    // # Get operation from left and right nodes
                    auto leftOper  = this->Visitor(oper->left);
                    auto rightOper = this->Visitor(oper->right);

                    // # build final operation
                    return leftOper + arithmeticOperator + rightOper;
                }
            }

            return "";
        }

        void FreeBinaryOperationFromMemory(BinaryOperation* binOp)
        {
            if(binOp != nullptr)
            {
                FreeBinaryOperationFromMemory(binOp->left);
                FreeBinaryOperationFromMemory(binOp->right);

                delete binOp;   
            }
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
        CallFunction()
        {
            this->kind = EBRANCH_TYPE::CALL_FUNCTION;
        }

        ~CallFunction()
        {
            MemTools::FreeVectorFromMemory(ArgumetList);
        }
    
    public:
        void InsertArgument(Expression* expr)
        {
            this->ArgumetList.push_back(expr);
        }
    
    public:
        std::string GetByteCode() override { return ""; }

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
        std::string GetByteCode() override { return ""; }
};

class ParameterDeclaration
{
    public:
        std::string name;
        TYPE_TOKEN type;

    public:
        ParameterDeclaration(){}
        ~ParameterDeclaration(){}
};

class FunctionDeclaration : public AstNode
{
    public:
        std::string name;
        std::string type;
        std::vector<ParameterDeclaration*> parameterList;

    public:
        std::vector<AstBranch*> BodyContent;

    public:
        FunctionDeclaration()
        {
            this->kind = EBRANCH_TYPE::FUNCTION_DECLARATION;
        }

        ~FunctionDeclaration()
        {
            MemTools::FreeVectorFromMemory(parameterList);
            MemTools::FreeVectorFromMemory(BodyContent);
        }

    public:
        bool IsFunctionEmpty()
        {
            return BodyContent.empty();
        }

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
        std::string GetByteCode() override { return ""; }
};

class AstBranch
{
    public:
        AstNode* entity;

    public:
        AstBranch(AstNode* entity):entity(entity){}
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