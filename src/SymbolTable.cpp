#include "../includes/SymbolTable.hpp"

SymbolTable::SymbolTable(){}

SymbolTable::~SymbolTable(){

	this->table.clear();
}

int SymbolTable::Add(std::string name, bool& varUp){

	// # check if exist, case yes, return then!
	for(int i = 0; i < this->table.size(); i++){
		
		if( this->table[ i ]->name == name ){		
		
			return this->table[ i ]->id;
		}
	}

	if( !varUp ){

		Console::Print(1, "Variable not declared in the scope! | Line: "+std::to_string(*this->linec)+" | "+name);
		exit(1);
	}

	// # Case not exist, make a new id
	Cell* tmp = new Cell();
	tmp->id = this->globalID;
	tmp->name = name;

	this->table.push_back(tmp);
	this->globalID++;

	return tmp->id;
}