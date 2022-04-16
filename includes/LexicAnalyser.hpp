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
#include <iostream>

#include "../includes/Console.hpp"
#include "../includes/SymbolTable.hpp"

class Lexer{

public:

	// # Here storage data processed
	std::string memory;
	
	uint32_t p1 = 0;
	uint32_t p2 = 0;
	uint8_t i = 0;
	uint8_t aux = 0;

	// # Scope Handler
	uint32_t scope;
	uint32_t current_scope;
	uint32_t deepLevel;

	bool hitted = false;
	bool numberFlag = false;
	bool stringScope = false;
	bool varUp = false;
	bool arrayUp = false;

	// # Counters
	uint32_t linec = 1; // # line counter

	// # Instances
	SymbolTable* sb_table;

public:
	Lexer(SymbolTable* ptable);
	~Lexer();

	std::string Processor(std::string& content);
	std::string Parser(std::string& chunk);
	
	void LEXER_ERROR(std::string msg);
	
	bool ValidateVarName(std::string& chunk);
	bool SubValidateVarName(char& target);
};