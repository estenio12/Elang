#include "../includes/SyntaticalAnalyser.hpp" 

Syntax::Syntax(SymbolTable* ptable){

	this->sb_table = ptable;
}

Syntax::~Syntax(){}

void Syntax::SYNTAX_ERROR(std::string msg){

	Console::Print(1, msg + " | Line: "+std::to_string(this->linec)+"");
	exit(1);
}

void Syntax::SYNTAX_ERROR(std::string msg, std::string& target){

	Console::Print(1, msg + " | Line: "+std::to_string(this->linec)+" | '" + target + "'");
	exit(1);
}

void Syntax::Processor(std::string& content){

	uint32_t p1 = 0;
	std::string tmpCopy;
	std::string blockCopy;

	while( content[ p1 ] != '\0' ){

		if( content[ p1 ] == '\n' ){

			++this->linec;
		}else{

			tmpCopy.push_back( content[ p1 ] );

			if( content[ p1 ] == this->sb_table->relational[ 3 ] && content[ p1 + 1 ] != this->sb_table->relational[ 3 ]){

				// # Token Processing
				this->TagIdentifier(tmpCopy);
				blockCopy += tmpCopy;

				if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ] ){
					
					this->MakeHistory(blockCopy);

					if( this->ValidateComposition(blockCopy) ){

						this->MakeSyntaxTree(blockCopy);
						this->history = 0;
						blockCopy.clear();
					}
					blockCopy.clear();
				}

				tmpCopy.clear();
			}
		}


		++p1;
	}
}

void Syntax::TagIdentifier( std::string& chunk ){

	uint8_t p = 0;
	uint8_t i = 0;
	this->map[ 0 ].clear();
	this->map[ 1 ].clear();
	
	while( chunk[ p ] != '\0' ){

		if( chunk[ p ] != this->sb_table->relational[ 3 ] && chunk[ p ] != this->sb_table->relational[ 4 ] ){

			if( chunk[ p ] == this->sb_table->delimiters[ 10 ] && this->splitHit == false){

				i = 1;
				this->splitHit = true;
			}else{

				this->map[ i ].push_back( chunk[ p ] );
			}
		}

		++p;
	}

	this->splitHit = false;
}

void Syntax::MakeHistory(std::string& chunk){

	std::vector<std::string> tmpStack = this->SplitTags(chunk);
	TagIdentifier(tmpStack[ 0 ]);

	if( this->history == 0 ){

		if( this->map[ 0 ] == "keyword" ){

			if( this->map[ 1 ] == this->sb_table->keywords[ 0 ] ||
			 	this->map[ 1 ] == this->sb_table->keywords[ 1 ] ){

				this->history = 1;
			}else if( this->map[ 1 ] == this->sb_table->keywords[ 2 ] ){

				this->history = 2;
			}else if( this->map[ 1 ] == this->sb_table->keywords[ 3 ] ||
					  this->map[ 1 ] == this->sb_table->keywords[ 4 ] ){

				this->history = 3;
			}else if( this->map[ 1 ] == this->sb_table->keywords[ 6 ] ){

				this->history = 5;
			}

		}else if( this->map[ 0 ] == "id" ){

			this->history = 4;
		}else{

			this->SYNTAX_ERROR("Syntax error: unrecognized keyword!");
		}
	}
}

bool Syntax::ValidateComposition(std::string& chunk){

	switch( this->history ){

		case 1:

			return this->ValidateVariables(chunk);
		break;
	}

	return false;
}

bool Syntax::ValidateVariables(std::string& chunk){

	// # It was decided to use the recursive method, with previous knowledge token

	uint8_t tmp_historic = 0;
	std::vector<std::string> tagStack;

	tagStack = this->SplitTags(chunk);

	for( int i = 0; i < tagStack.size(); i++ ){

		this->SubValidateVariables(tagStack[ i ], tmp_historic);
	}

	return true;
}

bool Syntax::SubValidateVariables(std::string& t_stack, uint8_t& p_historic ){

	// # 0 -> null; 1 -> keyword; 2 -> id; 3 -> oper; 4 -> '='; 5 -> '('; 6 -> ';'; 
	// # 7 -> '['; 8 -> ']' 9 -> ','; 10 -> datatype; 11 -> ')'; 

	this->TagIdentifier( t_stack );

	if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ] ){

		if( this->statFlag > 0 ){

			this->SYNTAX_ERROR("Syntax error: statement '(' opened, but never closed!");
		}

		if( this->arrayFlag > 0 ){

			this->SYNTAX_ERROR("Syntax error: statement '[' opened, but never closed!");
		}
	}

	switch( p_historic ){

		case 0:

			if( this->map[ 1 ] == this->sb_table->keywords[ 0 ] ||
				this->map[ 1 ] == this->sb_table->keywords[ 1 ] ){

				p_historic = 1;
			}else{

				this->SYNTAX_ERROR( "Syntax error: Invalid keyword!", this->map[ 1 ] );
			}
		break;

		case 1:

			if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ){

				p_historic = 2;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a variable name!");
			}
		break;

		case 2:

			if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ] ){

				p_historic = 6;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->relational[ 0 ] ){

				p_historic = 4;
			}else{

				this->SYNTAX_ERROR("Syntax error: Invalid operation!", this->map[ 1 ]);
			}
		break;

		case 3:

			if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 1 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 2 ] ){

				p_historic = 10;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 3 ] ){

				p_historic = 5;
				++this->statFlag;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a type data! ", this->map[ 1 ]);
			}
		break;

		case 4:

			if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 3 ] ){

				++this->statFlag;
				p_historic = 5;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 8 ] ){

				++this->arrayFlag;
				p_historic = 7;
			}else if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ||
					  this->map[ 0 ] == this->sb_table->typedata[ 1 ] ||
					  this->map[ 0 ] == this->sb_table->typedata[ 2 ] ){

				p_historic = 10;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a type data!", this->map[ 1 ]);
			}
		break;

		case 5: 

			if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 1 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 2 ] ){

				p_historic = 10;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a type data! ", this->map[ 1 ]);
			}
		break;

		case 6:break;

		case 7:

			if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 1 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 2 ] ){

				p_historic = 10;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a type data! ", this->map[ 1 ]);
			}
		break;

		case 8:

			if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ] ){

				p_historic = 6;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 10 ] ){

				p_historic = 9;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 9 ] ){

				if( this->arrayFlag <= 0 ){

					this->SYNTAX_ERROR("Syntax error: Invalid character! ", this->map[ 1 ]);
				}

				p_historic = 8;
				--this->arrayFlag;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected ';' or ','! ", this->map[ 1 ]);
			}
		break;

		case 9:

			if( this->map[ 0 ] == this->sb_table->typedata[ 0 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 1 ] ||
				this->map[ 0 ] == this->sb_table->typedata[ 2 ] ){

				p_historic = 10;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 3 ] ){

				p_historic = 5;
				++this->statFlag;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 8 ] ){

				p_historic = 7;
				++this->arrayFlag;
			}else{

				this->SYNTAX_ERROR("Syntax error: It's expected a type data! ", this->map[ 1 ]);
			}
		break;

		case 10:

			if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 4 ] ){

				if( this->statFlag <= 0 ){

					this->SYNTAX_ERROR("Syntax error: Invalid character! ", this->map[ 1 ]);
				}

				--this->statFlag;
				p_historic = 11;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 9 ] ){

				if( this->arrayFlag <= 0 ){

					this->SYNTAX_ERROR("Syntax error: Invalid character! ", this->map[ 1 ]);
				}

				--this->arrayFlag;
				p_historic = 8;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 10 ] ){

				if( this->arrayFlag <= 0 ){

					this->SYNTAX_ERROR("Syntax error: Invalid operator! This operator reserved to array variable.", this->map[ 1 ]);
				}
				p_historic = 9;
			}else if( this->map[ 0 ] == this->sb_table->typedata[ 3 ] ){

				p_historic = 3;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ]){

				p_historic = 6;
			}else{

				this->SYNTAX_ERROR("Syntax error: Invalid value!", this->map[ 1 ]);
			}
		break;

		case 11:

			if( this->map[ 0 ] == this->sb_table->typedata[ 3 ] ){

				p_historic = 3;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 9 ] ){

				p_historic = 8;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 10 ] ){

				p_historic = 9;
			}else if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 4 ] ){

				p_historic = 11;
				--this->statFlag;
			}else{

				this->SYNTAX_ERROR("Syntax error: Invalid statement operator!", this->map[ 1 ]);
			}
		break;
	}

	return false;
}

std::vector<std::string> Syntax::SplitTags(std::string& chunk){

	uint32_t p1 = 0;
	std::string tmpObj;
	std::vector<std::string> tmpStack;

	while( chunk[ p1 ] != '\0' ){

		tmpObj.push_back( chunk[ p1 ] );

		if( chunk[ p1 ] == '>' ){

			tmpStack.push_back(tmpObj);
			tmpObj.clear();
		}

		++p1;
	}

	tmpObj.clear();

	return tmpStack;
}

bool Syntax::SeekCloseStatement(std::string& chunk ,char& target){

	uint16_t p1 = 0;

	while( chunk[ p1 ] != '\0' ){

		if( chunk[ p1 ] == target ){

			return true;
		}

		if( chunk[ p1 ] == this->sb_table->delimiters[ 5 ] &&
			chunk[ p1 ] != target  ){

			return false;
		}

		if( chunk[ p1 ] == this->sb_table->delimiters[ 2 ] &&
			chunk[ p1 ] != target ){

			return false;
		}

		++p1;
	}

	return false;
}

void Syntax::MakeSyntaxTree(std::string& content){}