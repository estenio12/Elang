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

	Console::Print(1, msg + " | Line: "+std::to_string(this->linec)+" | " + target);
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
				tmpCopy.clear();

				// # Register what token is up context
				this->MakeHistory();

				// # Seek completely block code
				this->SeekBlockCode(content, blockCopy, p1);

				// # Validate Composition
				if( this->ValidateComposition(blockCopy) ){

					this->MakeSyntaxTree(blockCopy);
					this->history = 0;
					blockCopy.clear();
				}
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

			if( chunk[ p ] != this->sb_table->delimiters[ 10 ] ){

				this->map[ i ].push_back( chunk[ p ] );
			}else{

				i = 1;
			}
		}

		++p;
	}
}

void Syntax::MakeHistory(){


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

void Syntax::SeekBlockCode(std::string& content, std::string& blockCopy, uint32_t& pp1){

	uint32_t p1 = pp1 + 1;


	switch( this->history ){

		// # Separate the variable declaration block
		case 1:

			this->tmpStack.clear();

			while( content[ p1 ] != '\0' ){

				this->tmpStack.push_back( content[ p1 ] );

				if( content[ p1 ] == '>' && content[ p1 + 1 ] != '>'){

					// # Token Processing
					this->TagIdentifier(this->tmpStack);

					if( this->map[ 1 ][ 0 ] == this->sb_table->delimiters[ 5 ] ){

						blockCopy += this->tmpStack;
						this->tmpStack.clear();
						this->tokenFlag = true;
						break;
					}

					this->tmpStack.clear();
				}

				if( tokenFlag ){

					break;
				}

				++p1;
			}

			if( !tokenFlag ){

				this->SYNTAX_ERROR("Syntax error: Variable declaration never closed!");
			}

			this->tokenFlag = false;
			pp1 = p1;

		break;
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
	uint32_t index = 0;
	std::vector<std::string> tagStack;

	// # tmp_historic codex
	// # 
	// # 0 = null; 1 = var; 2 = id_declaration; 3 = del_1( ';' ); 4 = del_2( '(' )
	// # 5 = rel; 6 = id; 7 = num; 8 = string; 9 = oper; 10 = del_3 ( ')' )
	// # 11= rel others; 12 = del_3( [ ); 13 = del_4( ] ); 14 = del_5( , );

	tagStack = this->SplitTags(chunk);

	return this->SubValidateVariables(tagStack, tmp_historic, index);
}

bool Syntax::SubValidateVariables(std::vector<std::string>& t_stack,
									  uint8_t& p_historic,
									  uint32_t& index){

	// # 0 = null; 1 = var; 2 = id_declaration; 3 = del_1( ';' ); 4 = del_2( '(' )
	// # 5 = rel; 6 = id; 7 = num; 8 = string; 9 = oper; 10 = del_3 ( ')' )
	// # 11= rel others; 12 = del_3( [ ); 13 = del_4( ] ); 14 = del_5( , );

	this->TagIdentifier(t_stack[ index ]);
	
	if( this->map[ 0 ] == "del" && this->map[ 1 ][ 0 ] == ';' || 
		p_historic == 3 || 
		t_stack.size() == ( index - 1 ) ){

		if( this->statFlag ){

			this->SYNTAX_ERROR("Syntax error: \'(\' is openned, but never closed!");
		}

		if( this->arrayFlag ){

			this->SYNTAX_ERROR("Syntax error: \'[\' is openned, but never closed!");
		}

		return true;

	}else{

		switch( p_historic ){

			case 0:

				// # 0 = var; 1 = const
				if( this->map[ 1 ] == this->sb_table->keywords[ 0 ] ||
					this->map[ 1 ] == this->sb_table->keywords[ 1 ] ){

					p_historic = 1;
					this->SubValidateVariables(t_stack, p_historic, ++index);
				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid keyword!", this->map[ 1 ]);
				}
			break;

			case 1:

				if( this->map[ 0 ] == this->sb_table->typedata[0] ){

					p_historic = 2;
					this->SubValidateVariables(t_stack, p_historic, ++index);
				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid Identifier. ", this->map[ 1 ]);
				}
			break;

			case 2:

				// # 5 = ";";   
				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 5 ]){

					p_historic = 3;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->relational[ 0 ]){

					p_historic = 5;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: It's expected ( = ) or ( ; )", this->map[ 1 ]);
				}
			break;

			case 5:

				// # 3 = "("   
				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 3 ]){

					this->statFlag = true;
					p_historic = 4;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 8 ]){

					this->arrayFlag = true;
					p_historic = 12;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[0]){

					p_historic = 6;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[1]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[2]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid data!", this->map[ 1 ]);
				}
			break;

			case 4:

				if( this->map[ 0 ] ==  this->sb_table->typedata[0]){

					p_historic = 10;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[1]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[2]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid delimiter! it's expected a type data.", this->map[ 1 ]);
				}
			break;

			case 6: case 7: case 8:

				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 4 ]){

					this->statFlag = false;
					p_historic = 10;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 9 ]){

					this->arrayFlag = false;
					p_historic = 13;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 10 ]){

					p_historic = 14;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 3 ]){

					p_historic = 3;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 4 ]){

					p_historic = 11;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid sequence!", this->map[ 1 ]);
				}
			break;

			case 9:

				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 3 ]){

					this->statFlag = true;
					p_historic = 4;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 0 ]){

					p_historic = 6;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 1 ]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 2 ]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: it's expected a type data", this->map[ 1 ]);
				}
			break;

			case 10:

				if( this->map[ 0 ] ==  this->sb_table->typedata[ 3 ]){

					p_historic = 9;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 9 ]){

					this->arrayFlag = false;
					p_historic = 13;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 5 ]){

					p_historic = 3;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid sequence!", this->map[ 1 ]);
				}
			break;

			case 11:

				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 3 ]){

					p_historic = 4;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 0 ]){

					p_historic = 6;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 1 ]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[ 2 ]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: Invalid sequence!", this->map[ 1 ]);
				}
			break;

			case 12:

				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 3 ]){

					this->statFlag = true;
					p_historic = 4;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[0]){

					p_historic = 6;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[1]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[2]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: it's expected a type data", this->map[ 1 ]);
				}
			break;

			case 13:

				// # 5 = ";";   
				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 5 ]){

					p_historic = 3;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: it's expected a ';'", this->map[ 1 ]);
				}
			break;

			case 14:

				if( this->map[ 1 ][ 0 ] ==  this->sb_table->delimiters[ 3 ]){

					this->statFlag = true;
					p_historic = 4;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[0]){

					p_historic = 6;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[1]){

					p_historic = 7;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else if( this->map[ 0 ] ==  this->sb_table->typedata[2]){

					p_historic = 8;
					this->SubValidateVariables(t_stack, p_historic, ++index);

				}else{

					this->SYNTAX_ERROR("Syntax error: it's expected a type data", this->map[ 1 ]);
				}
			break;
		}
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

void Syntax::MakeSyntaxTree(std::string& content){

	
}