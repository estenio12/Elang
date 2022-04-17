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
//#include <vector>

#include "../includes/SymbolTable.hpp"
#include "../includes/Console.hpp"

class Syntax{

public:
	SymbolTable* sb_table;

	// # Tools
	std::string map[2];

	uint32_t linec = 0;

	// # 0 = reset;
	// # 1 = variables declaration; 2 = function declaration
	// # 3 = loop declaration; 4 = call identification
	// # 5 = if declaration
	uint8_t history = 0;

	// # SeekBlockCode Variables
	std::string tmpStack;
	bool tokenFlag = false;

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
	void MakeHistory();
	void SeekBlockCode(std::string& content,
					   std::string& bockcopy,
					   uint32_t& pp1);

	bool ValidateComposition(std::string& chunk);
	bool ValidateVariables(std::string& chunk);
	bool SubValidateVariables(std::vector<std::string>& t_stack,
							  uint8_t& p_historic,
							  uint32_t& p_p1);

	std::vector<std::string>& SplitTags(std::string& chunk);
};