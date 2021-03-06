#include <iostream>

#include "../includes/FileHandler.hpp"
#include "../includes/LexicAnalyser.hpp"
#include "../includes/SyntaticalAnalyser.hpp"
#include "../includes/SymbolTable.hpp"

int main(int argc, char* argv[]){

	SymbolTable* st = new SymbolTable();
	Lexer* lexer = new Lexer(st);
	Syntax* syntax = new Syntax(st);

	std::string	Data = File::Reader(argv[ 1 ]);
	lexer->Processor(Data);
	syntax->Processor(Data);

	//std::cout << "Raw: "<< Data << std::endl << std::endl;

	File::Writer(argv[ 1 ], Data);

	Console::Print(0, "Compiled with successfully!");

	// # free instance from memory
	delete lexer;
	delete syntax;
	delete st;

	return 0;
}