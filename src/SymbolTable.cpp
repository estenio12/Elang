#include "../includes/SymbolTable.hpp"

SymbolTable::SymbolTable(){}

SymbolTable::~SymbolTable(){

	this->table.clear();
}

int SymbolTable::Add(std::string name, bool& varUp){

	// # check if exist, case yes, return then!
	for(int i = 0; i < this->table.size(); i++){
		
		if( this->table[ i ]->name == name &&
			this->table[ i ]->scope <= *this->current_scope &&
			this->table[ i ]->deepLevel <= *this->current_deepLevel ){

			if( varUp ){

				this->SB_ERROR("Duplicated variable name!", name);
			}	
		
			return this->table[ i ]->id;
		}
	}

	if( !varUp ){

		this->SB_ERROR("Variable not declared in the scope!", name);

	}

	// # Case not exist, make a new id
	Cell* tmp = new Cell();
	tmp->id = this->globalID;
	tmp->name = name;
	tmp->scope = *this->current_scope;
	tmp->deepLevel = *this->current_deepLevel;

	this->table.push_back(tmp);
	this->globalID++;

	return tmp->id;
}

void SymbolTable::SB_ERROR(std::string msg, std::string& name){

	Console::Print(1, msg + " | Line: "+std::to_string(*this->linec)+" | "+name);
	exit(1);
}