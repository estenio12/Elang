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
	std::string keywords[10] = {
		"var","const","fun",
		"for","while","do",
		"return","if","elif",
		"else"
	};
	char operators[5] = {
		'+','-','*','/'
	};
	char delimiters[8] = {
		' ','{','}','(',')',';','\'','\"'
	};
	char relational[6] = {
		'=','|','&','>','<','!'
	};
	char number[11]{
		'0','1','2','3','4','5','6','7','8','9','.'
	};

	// # Here storage data processed
	std::string memory;
	
	uint8_t p1 = 0;
	uint8_t p2 = 0;
	uint8_t i = 0;
	uint8_t aux = 0;

	bool hitted = false;
	bool numberFlag = false;
	bool stringScope = false;

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