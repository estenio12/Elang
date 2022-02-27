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

class SymbolTableCell{

	std::string id;
	std::string type;
	std::string name;
	std::string value;
};

class Lexer{

public:
	std::vector<std::pair<std::string, std::string>> Variables;
	std::vector<std::pair<std::string, std::string>> Functions;
	std::vector<std::pair<std::string, std::string>> Delimiters;
	std::vector<std::pair<std::string, std::string>> Operators;
	std::vector<std::pair<std::string, std::string>> IncDec;
	std::vector<std::pair<std::string, std::string>> Conditional;
	std::vector<std::pair<std::string, std::string>> Loop;

	std::vector<SymbolTableCell> SymbolTable;

public:
	Lexer();
	~Lexer();

public:
	// # function for agregation
	std::string Processor(std::string& content);
	
	// # 
	std::string ChuckProcessor(std::string& chuck); 

	// # this function remove the character formatation
	void Formatter(std::string& content);

	// # this function apply lexic process
	void Reader(std::string& content);

};