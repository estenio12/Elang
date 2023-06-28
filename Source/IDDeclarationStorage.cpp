#include "../Include/IDDeclarationStorage.hpp"

IDDeclarationStorage::IDDeclarationStorage(){}

IDDeclarationStorage::~IDDeclarationStorage()
{
    this->IDTable.clear();
}

void IDDeclarationStorage::InsertID(IDModel* row)
{
    if(row != nullptr) this->IDTable.push_back(row);
}

bool IDDeclarationStorage::ExistIdentifier(std::string name)
{
    for(auto item : this->IDTable)
    {
        if(item->name == name)
        {
            return true;
        }
    }

    return false;
}

IDModel* IDDeclarationStorage::FindObjectIdentifier(std::string name)
{
    for(auto item : this->IDTable)
    {
        if(item->name == name)
        {
            return item;
        }
    }

    return nullptr;
}

IDModel* IDDeclarationStorage::CreateRow(std::string name, std::string value, std::string type, 
                                         std::string scopeName, int deep = 0)
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
    row->scopeName = scopeName;
    row->deep  = deep;

    return row; 
}
