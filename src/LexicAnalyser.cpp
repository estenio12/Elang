#include "../includes/LexicAnalyser.hpp"

Lexer::Lexer(){

	// # Load Tokens

	// # Load Variables
	this->Variables.push_back(std::make_pair("var", "t_var"));
	this->Variables.push_back(std::make_pair("const", "t_const"));

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

	// # Load Conditinals
	this->Conditional.push_back(std::make_pair("==", "t_eguals"));
	this->Conditional.push_back(std::make_pair("!=", "t_diff"));
	this->Conditional.push_back(std::make_pair("&&", "t_and"));
	this->Conditional.push_back(std::make_pair("||", "t_or"));

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
}

void Lexer::Formatter(std::string& content){

	// # spc = special character
	char spc[] = {'\t','\b','\v','\a'};
	std::string tmpContent;
	bool isTarget = false;
	uint16_t interator = 0;
	uint8_t i = 0;

	while( content[ interator ] != '\0' ){

		if( content[ 0 ] != ' ' ){ 

			isTarget = false;

			for( i = 0; i < 5; i++ ){

				if( content[ interator ] == spc[ i ] ||
					// # check if is a empty character
					( content[ interator ] == ' ' && content[ interator + 1 ] == ' ' ) ){

					isTarget = true;
					break;
				}
			}

			if( !isTarget ){
			
				tmpContent.push_back( content[ interator ] );
			}

		}

		++interator;
	}

	content = tmpContent;
	tmpContent.clear(); // free from memory
}

void Lexer::Reader(std::string& content){

	std::string current_word;
	std::string tmpContent;

	// # 
	bool hit = false;

	// # p1 reader pointer
	uint8_t p1 = 0;
	uint8_t p2 = 0; // # string look ahead
	uint8_t i = 0;

	while( content[ p1 ] != '\0' ){

		hit = false;

		// # Check if this next character is a delimiters
		if( !hit ){

			for( i = 0; i < this->Delimiters.size(); i++ ){
			
				if( content[ p1 ] == this->Delimiters[ i ].first[ 0 ] ){

					if( content[ p1 ] == '\"' || content[ p1 ] == '\'' ){

						p2 = p1 + 1;
						current_word.clear();
						stringScopeClose = false;

						while( content[ p2 ] != '\0' ){

							if( content[ p2 ] == '\"' || content[ p2 ] == '\'' ){

								this->stringScopeClose = true;
								break;
							}else{

								current_word.push_back( content[ p2 ] );
							}
							++p2;
						}

						if( this->stringScopeClose ){

							p1 = p2 + 1;
						}else{

							Console::Print("Error: string never closed!");
							exit(1);
						}
					}

					hit = true;
					break;
				}
			}
		}

		// # This condition execute when one special character finded
		if( hit ){

			tmpContent += this->ChuckProcessor( current_word );
			current_word.clear();
		}

		current_word.push_back( content[ p1 ] );
		++p1;
	}

	content = tmpContent;
	tmpContent.clear();
}

std::string Lexer::ChuckProcessor(std::string& chuck){

	if( !this->stringScopeClose ){
		
		this->ClearWS(chuck);
	}

	// # Check if a variable declaration
	for( c_pointer = 0; c_pointer < this->Variables.size(); c_pointer++ ){

		if( chuck == this->Variables[ c_pointer ].first ){

			return "<" + this->Variables[ c_pointer ].second +">";
		}
	}

	// # Check if a function declaration
	for( c_pointer = 0; c_pointer < this->Functions.size(); c_pointer++ ){

		if( chuck == this->Functions[ c_pointer ].first ){

			return "<" + this->Functions[ c_pointer ].second +">";
		}
	}

	// # Check if a Delimiters declaration
	for( c_pointer = 0; c_pointer < this->Delimiters.size(); c_pointer++ ){

		if( chuck == this->Delimiters[ c_pointer ].first ){

			return "<" + this->Delimiters[ c_pointer ].second +">";
		}
	}

	// # Check if a Operators declaration
	for( c_pointer = 0; c_pointer < this->Operators.size(); c_pointer++ ){

		if( chuck == this->Operators[ c_pointer ].first ){

			return "<" + this->Operators[ c_pointer ].second +">";
		}
	}

	// # Check if a Conditional declaration
	for( c_pointer = 0; c_pointer < this->Conditional.size(); c_pointer++ ){

		if( chuck == this->Conditional[ c_pointer ].first ){

			return "<" + this->Conditional[ c_pointer ].second +">";
		}
	}

	// # Check if a Loop declaration
	for( c_pointer = 0; c_pointer < this->Loop.size(); c_pointer++ ){

		if( chuck == this->Loop[ c_pointer ].first ){

			return "<" + this->Loop[ c_pointer ].second +">";
		}
	}

	// # case another verifications failure, will execute this
	for( c_pointer = 0; c_pointer < this->SymbolTable.size(); c_pointer++ ){

		if( chuck == this->SymbolTable[ c_pointer ].name){

			return "<" + this->SymbolTable[ c_pointer ].id +">";
		}
	}

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
	// # return new identification
	return "<id"+std::to_string( this->globalIDCounter )+">";
}

void Lexer::ClearWS(std::string& content){

	std::string tmp;
	uint8_t i = 0;

	while( content[ i ] != '\0' ){

		if( content[ i ] != ' ' ){

			tmp.push_back( content[ i ] );
		}

		++i;
	}

	content = tmp;
	tmp.clear();
}