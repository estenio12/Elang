#include <iostream>

#include "../includes/FileHandler.hpp"
#include "../includes/LexicAnalyser.hpp"

int main(int argc, char* argv[]){

	Lexer* lexer = new Lexer();

	std::string	Data = File::Reader(argv[ 1 ]);
	lexer->Processor(Data);

	//std::cout << "Raw: "<< Data << std::endl << std::endl;

	for(int i = 0; i < lexer->SymbolTable.size(); i++){

		std::cout << "id: " << lexer->SymbolTable[ i ].id << " | ";
		std::cout << "Name:" << lexer->SymbolTable[ i ].name << std::endl;
	}

	File::Writer(argv[ 1 ], Data);

	// # free instance from memory
	delete lexer;

	return 0;
}