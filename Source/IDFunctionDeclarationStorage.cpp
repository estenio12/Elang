#include "../Include/IDFunctionDeclarationStorage.hpp"

IDFunctionDeclarationStorage::IDFunctionDeclarationStorage(){}

IDFunctionDeclarationStorage::~IDFunctionDeclarationStorage()
{
    this->IDTable.clear();
}

void IDFunctionDeclarationStorage::InsertFunctionID(FunctionIDModel* row)
{
    if(row != nullptr) this->IDTable.push_back(row);
}

bool IDFunctionDeclarationStorage::ExistIdentifier(std::string name)
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

FunctionIDModel* IDFunctionDeclarationStorage::FindObjectIdentifier(std::string name, std::string type)
{
    for(auto item : this->IDTable)
    {
        if(item->name == name &&
           item->type == type )
        {
            return item;
        }
    }

    return nullptr;
}

FunctionIDModel* IDFunctionDeclarationStorage::FindObjectIdentifier(std::string name)
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

FunctionIDModel* IDFunctionDeclarationStorage::CreateRow(std::string name, std::string type)
{
    auto row = new FunctionIDModel(name, type);

    if(row == nullptr) 
    {
        std::cerr << "Function CreateRow: Out of memory\n";
        exit(EXIT_FAILURE);
    }

    return row; 
}
