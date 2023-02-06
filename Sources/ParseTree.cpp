#include "../Includes/ParseTree.hpp"

ParseTree::ParseTree()
{
    this->Build = new AST::AST_Node();
}

ParseTree::~ParseTree()
{
    Tree.clear();
}

void ParseTree::CreateNode(Dictionary Token)
{
    if(Token.first == AST::HIGH_ORDER ||
       Token.first == AST::DECAY_ORDER)
    {
        this->HandlerGlobalPowerLevel(Token.first);
    }
    else if(Token.second == NAMES::ASSIGNMENT)
    {
        if(Token.first == KEYWORDS::Assignment[KEYWORDS::EAssignment::MUL] ||
           Token.first == KEYWORDS::Assignment[KEYWORDS::EAssignment::DIV])
        {
            this->Build->PowerLevel = AST::MIDORDERVALUE + this->GlobalPowerLevel;
        }

        if(Token.first == KEYWORDS::Assignment[KEYWORDS::EAssignment::PLUS] ||
           Token.first == KEYWORDS::Assignment[KEYWORDS::EAssignment::LESS])
        {
            this->Build->PowerLevel = AST::LOWORDERVALUE + this->GlobalPowerLevel;
        }

        this->Build->Operator = Token.first;
    }
    else
    {
        if(this->Build->LeftContent.empty())
        {
            this->Build->LeftContent = Token.first;
        }
        else
        {
            this->Build->RightContent = Token.first;
            this->Commit();
        }
    }
}

inline void ParseTree::HandlerGlobalPowerLevel(std::string& Value)
{
    if(AST::HIGH_ORDER == Value)
    {
        this->GlobalPowerLevel += AST::HIGHORDERVALUE;
    }

    if(AST::DECAY_ORDER == Value)
    {
        this->GlobalPowerLevel -= AST::HIGHORDERVALUE;
    }
}

inline void ParseTree::Commit()
{
    AST::AST_Node* NewLeaf = new AST::AST_Node();
    NewLeaf->Operator     = this->Build->Operator;
    NewLeaf->LeftContent  = this->Build->LeftContent;
    NewLeaf->RightContent = this->Build->RightContent;
    NewLeaf->PowerLevel   = this->Build->PowerLevel;

    this->Tree.push_back(NewLeaf);
    this->Build->Reset();
}

inline void ParseTree::Sort()
{
    AST::AST_Node* aux = nullptr;

    for(int i = 0; i < Tree.size(); i++)
    {
        for(int j = 0; j < Tree.size(); j++)
        {
            if(Tree[j]->PowerLevel > Tree[j + 1]->PowerLevel)
            {
                aux = Tree[j];
                Tree[j] = Tree[j + 1];
                Tree[j + 1] = aux;
            }
        }
    }

    delete aux;
} 
