#include "../Includes/AST.hpp"

ParseTree::ParseTree()
{
    this->Root = new AST_Node();
}

ParseTree::~ParseTree()
{
    if(Root != nullptr)
    {
        delete Root;
    }
}

void ParseTree::CreateNode(std::string Content, std::string LeftContent)
{
    AST_Node* NewLeaf = new AST_Node();
    NewLeaf->Content      = Content;
    NewLeaf->LeftContent  = LeftContent;
    NewLeaf->RightContent = nullptr;
    NewLeaf->Parent       = nullptr;

    // # Tenho que criar alguma forma de verificar e atribuir 
    // # Um power level para cada nó, sempre usando o GlobalPowerLevel
    // # como referencia

    this->InsertNodeIntoTree(NewLeaf);
}

void ParseTree::InsertNodeIntoTree(AST_Node* NewLeaf)
{
    AST_Node* LastNode = this->GetLastNode(this->Root);
    NewLeaf->Parent = LastNode;

    LastNode->RightContent = NewLeaf;
}

AST_Node* ParseTree::GetLastNode(AST_Node* CurrentNode)
{
    if(CurrentNode != nullptr)
    {
        if(CurrentNode->RightContent == nullptr)
        {
            return CurrentNode;
        }
        else
        {
            return this->GetLastNode(CurrentNode->RightContent);
        }
    }

    return nullptr;
}

void ParseTree::DeleteTree()
{
    AST_Node* LastNode = this->GetLastNode(this->Root);
    this->DeleteNodeChild(LastNode);
}

void ParseTree::DeleteNodeChild(AST_Node* CurrentNode)
{
    if(CurrentNode != nullptr)
    {
        if(CurrentNode->RightContent != nullptr)
        {
            delete CurrentNode->RightContent;
        }

        if(CurrentNode->Parent != nullptr)
        {
            this->DeleteNodeChild(CurrentNode->Parent);
        }
    }
}