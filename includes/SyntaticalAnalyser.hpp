//#############################
//#  
//#  PROJECT WAS DEVELOPED FOR 
//#  MY GRADUATED THESES
//#  
//#  @AUTHOR: ESTENIO GARCIA
//#  LICENSE: MIT
//#  
//#############################

#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../includes/SymbolTable.hpp"
#include "../includes/Console.hpp"

#define debug(x) std::cout << "Debug: " << x << std::endl;

class Syntax{

public:
	SymbolTable* sb_table;

	// # Tools
	std::string map[2];

	uint32_t linec = 1;

	// # 0 = reset;
	// # 1 = variables declaration; 2 = function declaration
	// # 3 = loop declaration; 4 = call identification
	// # 5 = if declaration
	uint8_t history = 0;

	// # SeekBlockCode Variables
	std::string tmpStack;
	bool tokenFlag = false;
	bool splitHit = false;
	uint8_t statFlag = 0;
	uint8_t arrayFlag = 0;

	// # Memory
	std::string memory;

public:
	Syntax(SymbolTable* ptable);
	~Syntax();

	void Processor(std::string& content);
	void MakeSyntaxTree(std::string& content);
	void SYNTAX_ERROR(std::string msg);
	void SYNTAX_ERROR(std::string msg, std::string& target);
	void TagIdentifier(std::string& chunk);
	void MakeHistory(std::string& chunk);

	bool SeekCloseStatement(std::string& chunk, char& target); 
	bool ValidateComposition(std::string& chunk);
	bool ValidateVariables(std::string& chunk);
	bool SubValidateVariables(std::string& t_stack, uint8_t& p_historic);

	std::vector<std::string> SplitTags(std::string& chunk);
};