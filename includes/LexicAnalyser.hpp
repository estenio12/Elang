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

#include <vector>
#include <utility>
#include <string>
#include <cstdint>
#include <iostream>

#include "../includes/Console.hpp"

class SymbolTableCell{

public:
	std::string id;
	std::string type;
	std::string scope;
	std::string name;
	std::string value;

public:
	SymbolTableCell(
		std::string pid,
		std::string ptype,
		std::string pscope,
		std::string pname,
		std::string pvalue )
	:
		id(pid),
		type(ptype),
		scope(pscope),
		name(pname),
		value(pvalue){}
	~SymbolTableCell(){}

};

class Lexer{

public:
	std::vector<std::pair<std::string, std::string>> Variables;
	std::vector<std::pair<std::string, std::string>> Functions;
	std::vector<std::pair<std::string, std::string>> Delimiters;
	std::vector<std::pair<std::string, std::string>> Operators;
	std::vector<std::pair<std::string, std::string>> Conditional;
	std::vector<std::pair<std::string, std::string>> Loop;

	std::vector<SymbolTableCell> SymbolTable;

	// # Others Variables
	bool stringScopeClose = false;
	uint8_t c_pointer = 0; // c_pointer = chuck pointer
	uint32_t globalIDCounter = 0;

public:
	Lexer();
	~Lexer();

public:
	
	// # Process chuck by chuck for determinate your attribute
	std::string ChuckProcessor(std::string& chuck); 

	// # function for agregation
	void Processor(std::string& content);

	// # this function clear whitespace
	void ClearWS(std::string& content);

	// # this function remove the character formatation
	void Formatter(std::string& content);

	// # this function apply lexic process
	void Reader(std::string& content);

};