#include <iostream>

#include "../includes/FileHandler.hpp"
#include "../includes/LexicAnalyser.hpp"

int main(int argc, char* argv[]){

	Lexer* lexer = new Lexer();

	std::string	GetFileData = File::Reader(argv[ 1 ]);
	std::string GetLexicData = lexer->Processor(GetFileData);

	//std::cout << GetFileData << std::endl;

	File::Writer(argv[ 1 ], GetLexicData);

	// # free instance from memory
	delete lexer;

	return 0;
}