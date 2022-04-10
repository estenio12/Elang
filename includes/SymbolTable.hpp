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
	uint32_t scope = 0;
	uint32_t deepLevel = 0;
}Cell;

class SymbolTable{

public:
	// # Others
	uint32_t globalID = 1;
	uint32_t* linec;

	// # Scope Handler
	uint32_t* current_scope;
	uint32_t* current_deepLevel;
	
	// # Instances
	std::vector<Cell*> table;

public:
	SymbolTable();
	~SymbolTable();

	int Add(std::string name,
			bool& varUp);

	void SB_ERROR(std::string msg,
				  std::string& name);
};