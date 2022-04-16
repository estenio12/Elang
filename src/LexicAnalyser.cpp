#include "../includes/LexicAnalyser.hpp"

Lexer::Lexer(SymbolTable* ptable){

	this->sb_table = ptable;
	this->sb_table->linec = &this->linec;
	this->sb_table->current_scope = &this->current_scope;
	this->sb_table->current_deepLevel = &this->deepLevel;
}

Lexer::~Lexer(){}

std::string Lexer::Processor(std::string& content){

	// # storage
	std::string tmpCopy;

	while( content[ p1 ] != '\0' ){

		if( content[ p1 ] == '\n' ){

			// # add line count for debug
			++this->linec;
			this->memory.push_back(content[ p1 ]);
		// # Braces
		}else if( content[ p1 ] == '[' || content[ p1 ] == ']'){

			this->memory += "<del,";
			this->memory.push_back( ( content[ p1 ] == '[' ) ? '[' : ']' );
			this->memory.push_back('>');
		// # parentesis
		}else if( content[ p1 ] == '(' || content[ p1 ] == ')' ){

			this->memory += "<del,";
			this->memory.push_back( ( content[ p1 ] == '(' ) ? '(' : ')' );
			this->memory.push_back('>');
		// # Brackets
		}else if( content[ p1 ] == '{' || content[ p1 ] == '}'){

			this->memory += "<del,";
			this->memory.push_back( ( content[ p1 ] == '{' ) ? '{' : '}' );
			this->memory.push_back('>');

			// # Case find } simbol, subtract one for deep level
			if( content[ p1 ] == '}' ){


				// # if deep level less or eguals then zero, reset default values
				if( this->deepLevel <= 0 ){

					this->deepLevel = 0;
					this->current_scope = 0;
				}else{

					this->deepLevel--;
				}
			}
		// # Work with string
		}else if( content[ p1 ] == '\'' || content[ p1 ] == '\"'){

			// # process string data
			if( !this->stringScope ){				
				
				if( content[ p1 - 1] != '\\' ){	

					p2 = p1 + 1;
					tmpCopy.clear();
					this->stringScope = true;

					while( content [ p2 ] != '\0' ){

						tmpCopy.push_back( content[ p2 ] );

						if( content[ p2 + 1 ] == '\'' && content[ p2 ] != '\\' ||
							content[ p2 + 1 ] == '\"' && content[ p2 ] != '\\'){

							this->memory += "<str,"+tmpCopy+">";
							this->stringScope = false;
							break;
						}

						if( content[ p2 ] == '\\' ){

							tmpCopy.pop_back();
						}

						++p2;
					}

					if( this->stringScope ){

						this->LEXER_ERROR("String never closed! | Line: "+std::to_string(this->linec));
					}

					p1 = p2 + 1;
					tmpCopy.clear();
				}else{

					this->LEXER_ERROR("Invalid character! | Line: "+std::to_string(this->linec)+" | "+content[ p1 - 1] );
				}
			}else{

				this->LEXER_ERROR("String never closed! | Line: "+std::to_string(this->linec));
			}
		// # if before process not work, then, apply this!
		}else if( content[ p1 ] != ' ' ){

			tmpCopy.push_back( content[ p1 ] );
			this->hitted = false;

			if( content[ p1 ] == ';' ){

				this->hitted = true;
			}

			// # Check Operators
			if( !this->hitted ){

				// # Check compound operators
				for( i = 0; i < this->sb_table->size_oper; i++ ){

					if( content[ p1 + 1 ] == this->sb_table->operators[ i ] ||
						content[ p1 + 1 ] == '=' ){

						this->hitted = false;

						if( content[ p1 ] == '+' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}else if( content[ p1 ] == '-' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}else if( content[ p1 ] == '*' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}else if( content[ p1 ] == '/' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}else if( content[ p1 ] == '+' &&
							content[ p1 + 1 ] == '+'  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}else if( content[ p1 ] == '-' &&
							content[ p1 + 1 ] == '-'  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
							this->hitted = true;
						}
						break;
					}
				}

				// # Check singulaty operators
				for( i = 0; i < this->sb_table->size_oper; i++ ){

					if( content[ p1 + 1 ] == this->sb_table->operators[ i ] ){

						this->hitted = true;
						break;
					}
				}
			}

			// # Check delimiters
			if( !this->hitted ){
				
				for( i = 0; i < this->sb_table->size_del; i++ ){

					if( content[ p1 + 1 ] == this->sb_table->delimiters[ i ] ){

						this->hitted = true;
						break;
					}
				}
			}

			// # Check relational
			if( !this->hitted ){
			
				for( i = 0; i < this->sb_table->size_rel; i++ ){

					if( content[ p1 + 1 ] == this->sb_table->relational[ i ] ){

						// # Check if this pair
						if( content[ p1 ] == '=' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}else if( content[ p1 ] == '|' &&
							content[ p1 + 1 ] == '|'  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}else if( content[ p1 ] == '&' &&
							content[ p1 + 1 ] == '&'  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}else if( content[ p1 ] == '>' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}else if( content[ p1 ] == '<' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}else if( content[ p1 ] == '!' &&
							content[ p1 + 1 ] == '='  ){

							tmpCopy.push_back(content[ p1 + 1 ]);
							++p1;
						}

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
	for( i = 0; i < this->sb_table->size_keywords; i++ ){

		if( chunk == this->sb_table->keywords[ i ] ){

			// # Variable flag ups
			if( this->sb_table->keywords[ i ] == "var" ||
				this->sb_table->keywords[ i ] == "const" ||
				this->sb_table->keywords[ i ] == "fun" ){

				this->varUp = true;
			}

			// # Check for upscope
			if( this->sb_table->keywords[ i ] == "fun" ){

				this->scope++;
				this->current_scope = this->scope;
				this->deepLevel = 0;
			}

			// # Check for set deep level
			if( this->sb_table->keywords[ i ] == "for" || this->sb_table->keywords[ i ] == "while" ||
				this->sb_table->keywords[ i ] == "do"  || this->sb_table->keywords[ i ] == "if"  ||
				this->sb_table->keywords[ i ] == "elif"|| this->sb_table->keywords[ i ] == "else" ){

				this->deepLevel++;
			}

			return "<keywords,"+chunk+">";
		}
	}

	// # Check if the chunk is a operator
	for( i = 0; i < this->sb_table->size_oper; i++ ){

		if( chunk[ 0 ] == this->sb_table->operators[ i ] ){

			return "<oper,"+chunk+">";
		}
	}

	// # Check if the chunk is a delimiter
	for( i = 0; i < this->sb_table->size_del; i++ ){

		if( chunk[ 0 ] == this->sb_table->delimiters[ i ] ){

			return "<del,"+chunk+">";
		}
	}

	// # Check if the chunk is a relational
	for( i = 0; i < this->sb_table->size_rel; i++ ){

		if( chunk[ 0 ] == this->sb_table->relational[ i ] ){

			return "<rel,"+chunk+">";
		}
	}

	// # Check if the chunk is a number
	for( i = 0; i < chunk.size(); i++ ){

		this->numberFlag = false;

		for( aux = 0; aux < this->sb_table->size_num; aux++ ){

			if( chunk[ i ] == this->sb_table->number[ aux ] ){

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

		this->LEXER_ERROR("Invalid named variable! | Line: "+std::to_string(this->linec)+" | "+chunk);
	}

	std::string build = "<id,"+std::to_string(this->sb_table->Add(chunk, this->varUp))+">";
	this->varUp = false;

	return build;
}

void Lexer::LEXER_ERROR(std::string msg){

	Console::Print(1, msg);
	exit(1);
}

bool Lexer::ValidateVarName(std::string& chunk){

	// # Check if the chunk is a operator
	for( i = 0; i < this->sb_table->size_oper; i++ ){

		if( chunk[ 0 ] == this->sb_table->operators[ i ] ){

			return false;
		}
	}

	// # Check if the chunk is a delimiter
	for( i = 0; i < this->sb_table->size_del; i++ ){

		if( chunk[ 0 ] == this->sb_table->delimiters[ i ] ){

			return false;
		}
	}

	// # Check if the chunk is a relational
	for( i = 0; i < this->sb_table->size_rel; i++ ){

		if( chunk[ 0 ] == this->sb_table->relational[ i ] ){

			return false;
		}
	}

	for( i = 0; i < this->sb_table->size_num; i++ ){
		
		if( chunk[ 0 ]  == this->sb_table->number[ i ]){

			return false;
		}
	}

	// # check if variable name have a single character
	if( chunk.size() == 1 ){

		return true;
	}

	// # Check if varaibles name have a invalid character in your compound!
	for( i = 0; i < chunk.size(); i++ ){
		
		// # Here, i used a subRotine to check character by character
		if( !this->SubValidateVarName( chunk[ 1 ] ) ){

			return false;
		}
	}

	return true;
}

bool Lexer::SubValidateVarName(char& target){

	// # Check if the chunk is a operator
	for( i = 0; i < this->sb_table->size_oper; i++ ){

		if( target == this->sb_table->operators[ i ] ){

			return false;
		}
	}

	// # Check if the target is a delimiter
	for( i = 0; i < this->sb_table->size_del; i++ ){

		if( target == this->sb_table->delimiters[ i ] ){

			return false;
		}
	}

	// # Check if the target is a relational
	for( i = 0; i < this->sb_table->size_rel; i++ ){

		if( target == this->sb_table->relational[ i ] ){

			return false;
		}
	}

	return true;
}