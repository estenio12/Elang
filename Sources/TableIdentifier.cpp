#include "../Includes/TableIdentifier.hpp"

TableID::TableID(){}

TableID::~TableID()
{
    this->Table.clear();
}

void TableID::CreateID(std::string Name, TYPE TypeID)
{
    this->Table.push_back
    (
        new IDRow
        (
            ++this->GLOBALID, 
            Name, 
            DEFAULT_VALUE,
            TypeID,
            false
        )
    );
}

void TableID::SetType(TYPE NewTypeID, std::string TargetName)
{
    for(int i = 0; i < Table.size(); i++)
    {
        if(Table[i]->Name == TargetName)
        {
            Table[i]->TypeIdentidier = NewTypeID;
            break;
        }
    }
}

void TableID::SetValue(std::string NewValue, std::string TargetName)
{
    for(int i = 0; i < Table.size(); i++)
    {
        if(Table[i]->Name == TargetName)
        {
            Table[i]->Value = NewValue;
            break;
        }
    }
}

bool TableID::CheckIfExistIdentifier(std::string Name)
{
    for(int i = 0; i < Table.size(); i++)
    {
        if(Table[i]->Name == Name)
        {
            return true;
        }
    }

    return false;
}