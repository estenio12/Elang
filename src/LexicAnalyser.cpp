#include "../includes/LexicAnalyser.hpp"

Lexer::Lexer(){

	// # Load Tokens

	// # Load Variables
	/*this->Variables.push_back(std::make_pair("var", "t_var"));
	this->Variables.push_back(std::make_pair("const", "t_const"));*/

	// # Load functions
	this->Functions.push_back(std::make_pair("fun", "t_fun"));
	this->Functions.push_back(std::make_pair("return", "t_ret"));
	this->Functions.push_back(std::make_pair("if", "t_if"));
	this->Functions.push_back(std::make_pair("elif", "t_elif"));
	this->Functions.push_back(std::make_pair("else", "t_else"));

	// # Load Delimiters
	this->Delimiters.push_back(std::make_pair(";", "t_cmd_end"));
	this->Delimiters.push_back(std::make_pair(" ", "t_empty"));
	this->Delimiters.push_back(std::make_pair(":", "t_open_fun"));
	this->Delimiters.push_back(std::make_pair("\"","t_str"));
	this->Delimiters.push_back(std::make_pair("\'","t_str"));
	this->Delimiters.push_back(std::make_pair("(", "t_param_open"));
	this->Delimiters.push_back(std::make_pair(")", "t_param_close"));
	this->Delimiters.push_back(std::make_pair("{", "t_brace_open"));
	this->Delimiters.push_back(std::make_pair("}", "t_brace_close"));
	this->Delimiters.push_back(std::make_pair("[", "t_brecket_open"));
	this->Delimiters.push_back(std::make_pair("]", "t_brecket_close"));

	// # Load Operators
	this->Operators.push_back(std::make_pair("=", "t_set"));
	this->Operators.push_back(std::make_pair("+", "t_plus"));
	this->Operators.push_back(std::make_pair("-", "t_minus"));
	this->Operators.push_back(std::make_pair("/", "t_div"));
	this->Operators.push_back(std::make_pair("*", "t_mult"));
	this->Operators.push_back(std::make_pair("+=", "t_addself"));
	this->Operators.push_back(std::make_pair("-=", "t_subself"));
	this->Operators.push_back(std::make_pair("/=", "t_divself"));
	this->Operators.push_back(std::make_pair("*=", "t_multself"));
	this->Operators.push_back(std::make_pair("++", "t_inc"));
	this->Operators.push_back(std::make_pair("--", "t_dec"));

	// # Load Conditinals
	this->Conditional.push_back(std::make_pair("==", "t_eguals"));
	this->Conditional.push_back(std::make_pair("!=", "t_diff"));
	this->Conditional.push_back(std::make_pair("&&", "t_and"));
	this->Conditional.push_back(std::make_pair("||", "t_or"));
	this->Conditional.push_back(std::make_pair(">=", "t_goreq"));
	this->Conditional.push_back(std::make_pair("<=", "t_loreq"));
	this->Conditional.push_back(std::make_pair(">", "t_greatthen"));
	this->Conditional.push_back(std::make_pair("<", "t_lessthen"));

	// #  Load Loop
	this->Loop.push_back(std::make_pair("for", "t_for"));
	this->Loop.push_back(std::make_pair("while", "t_while"));
	this->Loop.push_back(std::make_pair("do", "t_do"));
}

Lexer::~Lexer(){

	// # Free Tokens
	this->Variables.clear();
	this->Functions.clear();
	this->Delimiters.clear();
	this->Operators.clear();
	this->Conditional.clear();
	this->Loop.clear();

	// # Free Symbol Table
	this->SymbolTable.clear();
}

void Lexer::Processor(std::string& content){

	// # Apply formatation over content
	this->Formatter(content);

	// # Apply Lexic Process
	this->Reader(content);

	// # Apply a cleaner empty tag
	this->ClearEmptyTag(content);
}

void Lexer::Formatter(std::string& content){

	// # spc = special character
	char spc[] = {'\t','\b','\v','\a'};
	std::string tmpContent;
	bool isTarget = false;
	uint16_t p = 0;
	uint8_t i = 0;

	while( content[ p ] != '\0' ){

		isTarget = false;

		for( i = 0; i < 5; i++ ){

			if( content[ p ] == spc[ i ] ||
				// # check if is a empty character
				( content[ p ] == ' ' && content[ p + 1 ] == ' ' ) ){

				isTarget = true;
				break;
			}
		}

		if( !isTarget ){
		
			tmpContent.push_back( content[ p ] );
		}

		++p;
	}

	content = tmpContent;
	tmpContent.clear(); // free from memory
}

void Lexer::Reader(std::string& content){

	std::string current_word;
	std::string tmpContent;

	// # p1 reader pointer
	uint16_t p1 = 0;
	uint16_t p2 = 0; // # string look ahead
	uint8_t i = 0;

	while( content[ p1 ] != '\0' ){

		current_word.clear();
		
		// # Check if this current character is whitespace
		if( this->isToken( content[ p1 ] ) ){

			if( content[ p1 ] != '\"'){

				current_word.push_back( content[ p1 ] );
			}

		}else if( this->isTokenRange( content[ p1 ], content[ p1 + 1 ] ) ){

			switch( this->t_type ){

				case 1:

					current_word.push_back( content[ p1 ] );
					current_word.push_back( content[ p1 + 1 ] );
					++p1;
					break;
				case 2:

					current_word.push_back( content[ p1 ] );
					break;
			}
		}else{

			if( this->stringScopeUp ){

				p2 = this->StringHandler(content, current_word, p1);

				if( p2 == 0 ){

					Console::Print(1, "Error: string never close!");
					exit(1);
				}

				p1 = p2;
				this->stringScopeUp = false;
			}else{

				this->ContentHandler(content, current_word, p1);
			}
		}

		// # check if this is a null string
		if( current_word.size() > 0 ){ 

			tmpContent += this->ChuckProcessor( current_word );
		}

		++p1;
	}

	content = tmpContent;
	tmpContent.clear();
}

std::string Lexer::ChuckProcessor(std::string& chuck){

	// # Check if a variable declaration
	for( c_pointer = 0; c_pointer < this->Variables.size(); c_pointer++ ){

		if( chuck == this->Variables[ c_pointer ].first ){

			this->SetOccurrence("token");
			return "<" + this->Variables[ c_pointer ].second +">";
		}
	}

	// # Check if a function declaration
	for( c_pointer = 0; c_pointer < this->Functions.size(); c_pointer++ ){

		if( chuck == this->Functions[ c_pointer ].first ){

			this->SetOccurrence("token");
			return "<" + this->Functions[ c_pointer ].second +">";
		}
	}

	// # Check if a Delimiters declaration

	for( c_pointer = 0; c_pointer < this->Delimiters.size(); c_pointer++ ){

		if( chuck == this->Delimiters[ c_pointer ].first ){

			if( chuck == ";" ){

				this->SetOccurrence("none");
			}else{

				this->SetOccurrence("token");
			}

			return "<" + this->Delimiters[ c_pointer ].second +">";
		}
	}

	// # Check if a Operators declaration
	for( c_pointer = 0; c_pointer < this->Operators.size(); c_pointer++ ){

		if( chuck == this->Operators[ c_pointer ].first ){

			this->SetOccurrence("token");
			return "<" + this->Operators[ c_pointer ].second +">";
		}
	}

	// # Check if a Conditional declaration
	for( c_pointer = 0; c_pointer < this->Conditional.size(); c_pointer++ ){

		if( chuck == this->Conditional[ c_pointer ].first ){

			this->SetOccurrence("token");
			return "<" + this->Conditional[ c_pointer ].second +">";
		}
	}

	// # Check if a Loop declaration
	for( c_pointer = 0; c_pointer < this->Loop.size(); c_pointer++ ){

		if( chuck == this->Loop[ c_pointer ].first ){

			this->SetOccurrence("token");
			return "<" + this->Loop[ c_pointer ].second +">";
		}
	}

	// # case another verifications failure, will execute this
	for( c_pointer = 0; c_pointer < this->SymbolTable.size(); c_pointer++ ){

		if( chuck == this->SymbolTable[ c_pointer ].name){

			this->SetOccurrence("token");
			return "<" + this->SymbolTable[ c_pointer ].id +">";
		}
	}

	if( this->isDeclared( chuck ) ){

	++this->globalIDCounter;
	this->SymbolTable.push_back(
		*new SymbolTableCell(
			"id"+std::to_string(globalIDCounter), // # ID
			"underfined", // # Type
			"global",	  // # scope
			chuck,		  // # name
			"underfined"  // # value
			)
		);
	}else{

		Console::Print(1, "Variable not declared in the scope | ( "+chuck+" )");
		exit(1);
	}

	// # Register new occurrence
	this->SetOccurrence("id");
	// # return new identification
	return "<id"+std::to_string( this->globalIDCounter )+">";
}

void Lexer::ClearWS(std::string& content){

	std::string tmp;
	uint8_t i = 0;

	while( content[ i ] != '\0' ){

		if( content[ i ] != ' '){

			tmp.push_back( content[ i ] );
		}

		++i;
	}

	content = tmp;
	tmp.clear();
}

bool Lexer::isToken(char content){

	this->t_interator = 0;

	// # Check if this character is a delimiters
	for( this->t_interator = 0; this->t_interator < this->Delimiters.size(); this->t_interator++ ){
		
		if( content == this->Delimiters[ this->t_interator ].first[ 0 ] ){

			if( content == '\"' || content == '\'' ){

				this->stringScopeUp = true;
			}

			return true;
			break;
		}
	}

	return false;
}

bool Lexer::isTokenRange(char p1, char p2){

	this->t_interator = 0;

	// # Check if current and next character is a Operators
	for( this->t_interator = 0; this->t_interator < this->Operators.size(); this->t_interator++ ){
		
		if( p1 == this->Operators[ this->t_interator ].first[ 0 ] ){
			
			for( this->t_aux = 0; this->t_aux < this->Operators.size(); t_aux++){

				if( p2 == this->Operators[ this->t_aux ].first[ 0 ] ){

					this->t_type = 1;
					return true;
				}
			}

			this->t_type = 2;
			return true;
			break;
		}
	}

	// # Check if current and next character is a Conditions
	for( this->t_interator = 0; this->t_interator < this->Conditional.size(); this->t_interator++ ){
		
		if( p1 == this->Conditional[ this->t_interator ].first[ 0 ] ){
			
			for( this->t_aux = 0; this->t_aux < this->Conditional.size(); t_aux++){

				if( p2 == this->Conditional[ this->t_aux ].first[ 0 ] ){

					this->t_type = 1;
					return true;
				}
			}

			this->t_type = 2;
			return true;
			break;
		}
	}

	return false;
}

uint16_t Lexer::StringHandler(std::string& content, std::string& tmp, uint16_t pointer){

	uint16_t p2 = pointer;

	while( content[ p2 ] != '\0' ){

		if( content[ p2 ] == '\"' || content[ p2 ] == '\'' ){

			return p2;
		}else{

			tmp.push_back( content[ p2 ] );
		}

		++p2;
	}

	return 0;
}

void Lexer::ContentHandler(std::string& content, std::string& tmp, uint16_t& pointer){

	uint16_t p2 = pointer;
	uint8_t i = 0;

	while( content[ p2 ] != '\0' ){

		tmp.push_back( content[ p2 ] );

		if( this->isToken(content[ p2 + 1 ]) ){ break;}
		if( this->isTokenRange(content[ p2 + 1 ], ' ') ){ break;}

		++p2;
	}

	this->stringScopeUp = false;
	pointer = p2;
}

void Lexer::ClearEmptyTag(std::string& content){

	uint16_t p1 = 0; // # pointer 01

	std::string current_word;
	std::string tmpContent;

	while( content[ p1 ] != '\0' ){

		current_word.push_back( content[ p1 ] );
		
		if( content[ p1 ] == '>' ){

			if( current_word != "<t_empty>" ){

				tmpContent += current_word;
			}
			current_word.clear();
		}

		++p1;
	}

	content = tmpContent;
	tmpContent.clear();
}

bool Lexer::isDeclared(std::string& content){

	for( this->t_aux_isDec = 0; this->t_aux_isDec < this->SymbolTable.size(); this->t_aux_isDec++ ){

		if( content == this->SymbolTable[ this->t_aux_isDec ].name ){

			return true;
		}
	}

	// # check if last occurrence is difference of token
	// # if the last occurrence is a token, then create variable
	if( this->occurrence != "token" ){

		return true;
	}

	return false;
}

void Lexer::SetOccurrence(std::string content){

	this->occurrence = content;
}