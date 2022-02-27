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
	this->Delimiters.push_back(std::make_pair(";", "t_block_close"));
	this->Delimiters.push_back(std::make_pair(" ", "t_empty"));
	this->Delimiters.push_back(std::make_pair("\"","t_str"));
	this->Delimiters.push_back(std::make_pair("\'","t_str"));
	this->Delimiters.push_back(std::make_pair("(", "t_param_open"));
	this->Delimiters.push_back(std::make_pair(")", "t_param_close"));
	this->Delimiters.push_back(std::make_pair("{", "t_brace_open"));
	this->Delimiters.push_back(std::make_pair("}", "t_brace_close"));
	this->Delimiters.push_back(std::make_pair("[", "t_brecket_open"));
	this->Delimiters.push_back(std::make_pair("]", "t_brecket_close"));

	// # Load Operators
	this->Operators.push_back(std::make_pair("+", "t_plus"));
	this->Operators.push_back(std::make_pair("-", "t_minus"));
	this->Operators.push_back(std::make_pair("/", "t_div"));
	this->Operators.push_back(std::make_pair("*", "t_mult"));
	this->Operators.push_back(std::make_pair("+=", "t_addself"));
	this->Operators.push_back(std::make_pair("-=", "t_subself"));
	this->Operators.push_back(std::make_pair("/=", "t_divself"));
	this->Operators.push_back(std::make_pair("*=", "t_multself"));

	// # Load Incremeters and Decrementers
	this->IncDec.push_back(std::make_pair("=", "t_set"));
	this->IncDec.push_back(std::make_pair("++", "t_inc"));
	this->IncDec.push_back(std::make_pair("--", "t_dec"));

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
	this->IncDec.clear();
	this->Conditional.clear();
	this->Loop.clear();

	// # Free Symbol Table
	this->SymbolTable.clear();
}

std::string Lexer::Processor(std::string& content){

	// # Apply formatation over content
	this->Formatter(content);

	// # Apply Lexic Process
	this->Reader(content);

	return "none";
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

	std::string tmpContent;
	char tmpStack;
	uint32_t interator = 0;
	uint8_t pointer = 0;

	bool hit = false;

	while( content[ interator ] != '\0' ){

		tmpContent.push_back(content[ interator ]);
		
		// # first step, separete by chuck
		for( pointer = 0; pointer < this->Delimiters.size(); pointer++ ){

			if( content[ interator ] == this->Delimiters[ pointer ].first[ 0 ] ){

				hit = true;

			}
		}

		if( !hit ){
			
			this->ChuckProcessor(tmpContent);
		}

		++interator;
	}
}

std::string Lexer::ChuckProcessor(std::string& chuck){

	std::cout << "TES: " << chuck << std::endl;

	return "none";
}