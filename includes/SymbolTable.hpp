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

	// # Tokens arrays size
	const static size_t size_keywords = 13;
	const static size_t size_oper = 4;
	const static size_t size_del  = 11;
	const static size_t size_rel  = 6;
	const static size_t size_num  = 11;

	std::string keywords[size_keywords] = {
		"var","const","fun",
		"for","while","return",
		"if","elif","else",
		"in","at","break"
	};
	char operators[size_oper] = {
		'+','-','*','/'
	};
	char delimiters[size_del] = {
		' ','{','}','(',')',';','\'','\"','[',']',','
	};
	char relational[size_rel] = {
		'=','|','&','>','<','!'
	};
	char number[size_num]{
		'0','1','2','3','4','5','6','7','8','9','.'
	};


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