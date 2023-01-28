// #
// # This project was licensed by MIT
// # @author: Estenio Garcia 
// #

#ifndef TABLEIDENTIFIER_H
#define TABLEIDENTIFIER_H

#include <cstdint>
#include <string>
#include <vector>

static const std::string DEFAULT_ENTITY = "NONE";
static const std::string DEFAULT_VALUE = "0";

enum TYPE
{
    UNDEFINED,
    BOOL,
    STRING,
    CHAR,
    NUMBER
};

class IDRow
{
    public:

    public:
        uint32_t ID         = 0;
        std::string Name    = DEFAULT_ENTITY;
        std::string Value   = DEFAULT_VALUE;
        TYPE TypeIdentidier = TYPE::UNDEFINED;
        bool IsConstant    = false;

    public:
        IDRow(uint32_t ID,
              std::string Name ,
              std::string Value = "0",
              TYPE TypeID = TYPE::UNDEFINED,
              bool IsConstant = false):
              ID(ID),
              Name(Name),
              Value(Value),
              TypeIdentidier(TypeID),
              IsConstant(IsConstant)
              {}
};

class TableID
{
    private:
        std::vector<IDRow*> Table;
        uint32_t GLOBALID = 0;

    public:
        TableID();
        ~TableID();

    public:
        void CreateID(std::string Name, TYPE TypeID = TYPE::UNDEFINED, bool IsConstant = false);
        void SetType(TYPE NewTypeID, std::string TargetName);
        void SetValue(std::string NewValue, std::string TargetName);

    public:
        bool CheckIfExistIdentifier(std::string Name);
};

#endif