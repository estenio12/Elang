#include "../includes/LexicAnalyser.hpp"

Lexer::Lexer(SymbolTable* ptable){

	this->sb_table = ptable;
}

Lexer::~Lexer(){}

std::string Lexer::Processor(std::string& content){

	// # storage
	std::string tmpCopy;

	while( content[ p1 ] != '\0' ){

		if( content[ p1 ] == '\n' ){

			++this->linec;
		}else if( content[ p1 ] != ' ' ){

			tmpCopy.push_back( content[ p1 ] );

			if( content[ p1 ] == ';' ){

				this->hitted = true;
			}

			// # Check Operators
			if( !this->hitted ){

				for( i = 0; i < 5; i++ ){

					if( content[ p1 + 1 ] == this->operators[ i ] ){

						this->hitted = true;
						break;
					}
				}
			}

			// # Check delimiters
			if( !this->hitted ){
				
				for( i = 0; i < 8; i++ ){

					if( content[ p1 + 1 ] == this->delimiters[ i ] ){

						this->hitted = true;
						break;
					}
				}
			}

			// # Check statements
			if( !this->hitted ){

				for( i = 0; i < 6; i++ ){

					if( content[ p1 + 1 ] == this->statements[ i ] ){

						this->hitted = true;
						break;
					}
				}
			}

			// # Make parse
			if( this->hitted ){

				this->memory += this->Parser(tmpCopy);
				tmpCopy.clear();
				this->hitted = false;
			}
		}

		++p1;
	}

	content.clear();

	return content = this->memory;
}

std::string Lexer::Parser(std::string& chunk){

	//std::cout << "Debug Parser: " << chunk << std::endl;

	// # Check if the chunk is a keyword
	for( i = 0; i < 10; i++ ){

		if( chunk == this->keywords[ i ] ){

			return "<keywords,"+chunk+">";
		}
	}

	// # Check if the chunk is a operator
	for( i = 0; i < 5; i++ ){

		if( chunk[ 0 ] == this->operators[ i ] ){

			return "<oper,"+chunk+">";
		}
	}

	// # Check if the chunk is a delimiter
	for( i = 0; i < 8; i++ ){

		if( chunk[ 0 ] == this->delimiters[ i ] ){

			return "<del,"+chunk+">";
		}
	}

	// # Check if the chunk is a statement
	for( i = 0; i < 6; i++ ){

		if( chunk[ 0 ] == this->statements[ i ] ){

			return "<stat,"+chunk+">";
		}
	}

	// # Check if the chunk is a number
	for( i = 0; i < chunk.size(); i++ ){

		this->numberFlag = false;

		for( aux = 0; aux < 11; aux++ ){

			if( chunk[ i ] == this->number[ aux ] ){

				this->numberFlag = true;
				break;
			}
		}

		if( !this->numberFlag ){ break; }
	}

	// # if this is a number, return number
	if( this->numberFlag ){

		return "<number,"+chunk+">";
	}

	// # validate variable name
	if( !this->ValidateVarName(chunk) ){

		this->LEXER_ERROR("Cannot start variable name with a number! | Line: "+std::to_string(this->linec)+" | "+chunk);
	}

	return "<id,"+std::to_string(this->sb_table->Add(chunk))+">";
}

void Lexer::LEXER_ERROR(std::string msg){

	Console::Print(1, msg);
	exit(1);
}

bool Lexer::ValidateVarName(std::string& chunk){

	// # Check if the chunk is a operator
	for( i = 0; i < 5; i++ ){

		if( chunk[ 0 ] == this->operators[ i ] ){

			return false;
		}
	}

	// # Check if the chunk is a delimiter
	for( i = 0; i < 8; i++ ){

		if( chunk[ 0 ] == this->delimiters[ i ] ){

			return false;
		}
	}

	// # Check if the chunk is a statement
	for( i = 0; i < 6; i++ ){

		if( chunk[ 0 ] == this->statements[ i ] ){

			return false;
		}
	}

	for( i = 0; i < 11; i++ ){
		
		if( chunk[ 0 ]  == this->number[ i ]){

			return false;
		}
	}

	return true;
}