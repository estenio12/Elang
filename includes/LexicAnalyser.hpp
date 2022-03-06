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
	bool stringScopeUp = false;
	uint8_t c_pointer = 0; // c_pointer = chuck pointer
	uint8_t t_interator = 0;

	// # This variables identify what type token
	uint8_t t_type = 0;
	uint8_t t_aux = 0;

	// # This variables used to check if variables declared
	uint16_t t_aux_isDec = 0;

	// # this variables special character
	const std::string numbers = "1234567890.";
	bool numberHit = false;
	bool numberReal = false;
	uint8_t n_aux_1 = 0;
	uint8_t n_aux_2 = 0;

	// # Global Storage Varaibles
	uint32_t globalIDCounter = 0;

		// # this variable storage the last command readed
	std::string occurrence = "none";

public:
	Lexer();
	~Lexer();

public:
	
	// # Process chuck by chuck for determinate your attribute
	std::string ChuckProcessor(std::string& chuck); 

	// # this function check if this character is a token
	bool isToken(char content);

	bool isTokenRange(char p1, char p2);

	bool isDeclared(std::string& content);

	bool isNumber(std::string& content);

	// # this function search string close scope
	uint16_t StringHandler(std::string& content, std::string& tmp, uint16_t pointer);

	// # this function search end current word
	void ContentHandler(std::string& content, std::string& tmp, uint16_t& pointer);

	// # function for agregation
	void Processor(std::string& content);

	// # this function clear whitespace
	void ClearWS(std::string& content);

	// # this function remove the character formatation
	void Formatter(std::string& content);

	// # this function apply lexic process
	void Reader(std::string& content);

	// # this function clear empty tags
	void ClearEmptyTag(std::string& content);

	// # this function change for the new occurrence
	void SetOccurrence(std::string content);
};