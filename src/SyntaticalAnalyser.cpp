#include <../includes/SyntaticalAnalyser.hpp>

Syntax::Syntax(SymbolTable* ptable){

	this->sb_table = ptable;
}

Syntax::~Syntax(){}

void Syntax::SYNTAX_ERROR(std::string msg){

	Console::Print(1, msg + " | Line: "+std::to_string(this->linec)+"");
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

			if( content[ p1 ] == '>' && content[ p1 + 1 ] != '>'){

				// # Token Processing
				this->TagIdentifier(tmpCopy);
				blockCopy += tmpCopy;
				tmpCopy.clear();

				// # Register what token is up context
				this->MakeHistory();

				// # Seek completly block code
				this->SeekBlockCode(content, blockCopy, p1);

				// # Validate Composition
				if( this->ValidateComposition(blockCopy) ){

					this->MakeSintaxTree(blockCopy);
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
	
	while( chunk[ p ] != '\0' ){

		if( chunk[ p ] != '<' || chunk[ p ] != '>' ){

			if( chunk[ p ] != ',' ){

				this->map[ i ].push_back( chunk[ p ] );
			}else{

				i = 1;
			}
		}
	}
}

void Syntax::MakeHistory(){

	if( this->history == 0 ){

		if( this->map[ 0 ] == "keywords" ){

			switch( this->map[ 1 ] ){

				case "var" || "const":

					this->history = 1;
					break;

				case "fun":

					this->history = 2;
					break;

				case "for" || "while":

					this->history = 3;
					break;

				case "if":

					this->history = 5;
					break;

			}
			
		}else if( this->map[ 0 ] == "id" ){

			this->history = 4;
		}else{

			this->SYNTAX_ERROR("Syntax error!");
		}
	}
}

void Syntax::SeekBlockCode(std::string& content, std::string& blockCopy, uint32_t& pp1){

	uint32_t p1 = pp1 + 1;

	switch( this->history ){

		// # Separate the variable declaration block
		case 1:

			while( content[ p1 ] != '\0' ){

				this->tmpStack.push_back( content[ p1 ] );

				if( content[ p1 ] == '>' && content[ p1 + 1 ] != '>'){

					// # Token Processing
					this->TagIdentifier(this->tmpStack);

					if( this->map[ 0 ] == "del" && this->map[ 1 ][ 0 ] == ';' ){

						blockCopy += this->tmpStack;
						this->tmpStack.clear();
						this->tokenFlag = true;
						break;
					}
				}
			}

			if( !tokenFlag ){

				this->SYNTAX_ERROR("Syntax error!");
			}

			this->tokenFlag = false;
			break;
	}
}

bool Syntax::ValidateComposition(std::string& chunk){

	switch( this->history ){

		case 1:

			return this->ValidateVariables(chunk);
			break;
	}
}

bool Syntax::ValidateVariables(std::string& chunk){

	// # Was decide use recursive method, 
	// # with acknoledge token before

	uint8_t tmp_historic = 0;
	uint32_t index = 0;
	std::vector<std::string> tagStack;

	// # tmp_historic codex
	// # 
	// # 0 = null; 1 = var; 2 = id; 3 = del_1( ';' ); 4 = del_2( '(' )
	// # 5 = rel; 6 = id; 7 = num; 8 = string; 9 = oper;

	tagStack = this->SplitTags(chunk);

	return this->SubValidateVariables(tagStack, tmp_historic, index);
}

bool Syntax::SubValidateVariables(std::vector<std::string>& t_stack,
									  uint8_t& p_historic,
									  uint32_t& p_p1){

	// # 0 = null; 1 = var; 2 = id; 3 = del_1( ';' ); 4 = del_2( '(' )
	// # 5 = rel; 6 = id; 7 = num; 8 = string; 9 = oper;

	this->TagIdentifier(t_stack[ index ]);
	
	if( this->map[ 0 ] == "del" && this->map[ 1 ][ 0 ] == ';'){

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

					this->SYNTAX_ERROR("Syntax error!", t_stack[ index ]);
				}
				break;

			case 1:

				if( this->map[ 0 ] == "id" ){

					p_historic = 2;
					this->SubValidateVariables(t_stack, p_historic, ++index);
				}else{

					this->SYNTAX_ERROR("Syntax error!", t_stack[ index ]);
				}
				break;

			case 2:

				// # 5 = ";";   
				if( this->map[ 0 ] ==  this->sb_table->delimiters[ 5 ]){

					p_historic = 3;
					this->SubValidateVariables(t_stack, p_historic, ++index);
				}else if( this->map[ 0 ] ==  this->sb_table->relational[ 0 ]){

					p_historic = 5;
					this->SubValidateVariables(t_stack, p_historic, ++index);
				}else{

					this->SYNTAX_ERROR("Syntax error!", t_stack[ index ]);
				}
				break;
		}
	}

}

std::vector<std::string>& SplitTags(std::string& chunk){

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