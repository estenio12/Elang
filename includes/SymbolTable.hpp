//#############################
//#  
//#  PROJECT DEVELOPED FOR 
//#  GRADUATED THESES
//#  
//#  @AUTHOR: ESTENIO GARCIA
//#  LICENSE: MIT
//#  
//#############################

#pragma once
#include <cstring>
#include <string>
#include <cstdint>
#include <vector>

#include "../includes/Console.hpp"

typedef struct Cell{

	int id = 0;
	std::string name;
}Cell;

class SymbolTable{

public:
	uint32_t globalID = 1;
	std::vector<Cell*> table;

public:
	SymbolTable();
	~SymbolTable();

	int Add(std::string name);
};