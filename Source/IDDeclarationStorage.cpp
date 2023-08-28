#include "../Include/IDDeclarationStorage.hpp"

IDStorage::IDStorage(){}

IDStorage::~IDStorage()
{
    this->IDTable.clear();
}

void IDStorage::InsertID(IDModel* row)
{
    if(row != nullptr) this->IDTable.push_back(row);
}

bool IDStorage::ExistIdentifier(std::string name, std::string scopeName, int deep)
{
    for(auto item : this->IDTable)
    {
        if(item->name == name && 
           item->deep <= deep &&
           item->isEnable     &&
           (item->scopeName == scopeName ||
            item->scopeName == STANDARD_SCOPE_NAME::GLOBALSCOPE))
        {
            return true;
        }
    }

    return false;
}

IDModel* IDStorage::FindObjectIdentifier(std::string name)
{
    for(auto item : this->IDTable)
    {
        if(item->name == name && item->isEnable)
        {
            return item;
        }
    }

    return nullptr;
}

IDModel* IDStorage::CreateRow(std::string name, std::string value, std::string type, std::string typeValue, 
                              std::string scopeName, int IDScopeTable, int deep = 0, bool isConstant = false)
{
    IDModel* row = new IDModel();

    if(row == nullptr) 
    {
        std::cerr << "CreateRow: Out of memory\n";
        exit(EXIT_FAILURE);
    }

    row->ID    = ++this->globalIdCounter;
    row->name  = name;
    row->value = value;
    row->type  = type;
    row->typeValue = typeValue;
    row->scopeName = scopeName;
    row->deep      = deep;
    row->IDScopeTable = IDScopeTable; 

    return row; 
}

void IDStorage::RemoveID(int ID)
{
    for(int i = 0; i < this->IDTable.size(); i++)
    {
        if(this->IDTable[i]->IDScopeTable == ID)
        {
            this->IDTable[i]->isEnable = false;
        }
    }
}

void IDStorage::PrintDebug()
{
    for(int i = 0; i < this->IDTable.size(); i++)
    {
        std::cout << "Debug IDTable: " << this->IDTable[i]->name << " | " << this->IDTable[i]->IDScopeTable << "\n";
    }
}

