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

	// # checker size
	const static size_t size_keywords = 13;
	const static size_t size_oper = 4;
	const static size_t size_del  = 11;
	const static size_t size_rel  = 6;
	const static size_t size_num  = 11;

	std::string keywords[size_keywords] = {
		"var","const","fun",
		"for","while","do",
		"return","if","elif",
		"else","in","at","break"
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

	// # Here storage data processed
	std::string memory;
	
	uint32_t p1 = 0;
	uint32_t p2 = 0;
	uint8_t i = 0;
	uint8_t aux = 0;

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