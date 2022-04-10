#include "../includes/FileHandler.hpp"

std::string File::GetFileName(char* path){

	std::string tmpFileName;

	for(int i = 0; i < strlen(path); i++){

		if( path[ i ] == '.' ){

			break;
		}

		tmpFileName.push_back( path[ i ] );
	}

	return tmpFileName;
}

std::string File::Reader(char* path){

	std::fstream fileHandle;
	std::string content;
	std::string pointer;
	
	fileHandle.open(path, std::ios::in);

	if( fileHandle.is_open() && fileHandle.good() ){
	
		// # Get content from file
		while( std::getline(fileHandle, pointer) ){

			content += pointer;
			content.push_back('\n');
		}

		// # check if file is empty
		if( content.size() <= 3 ){

			fileHandle.close();
			Console::Print(1, "Invalid File!");
			exit(1);
		}

	}else{

		fileHandle.close();
		Console::Print(1, "Error: File cannot be readed!");
		exit(1);
	}

	// # free from memory
	fileHandle.close();
	pointer.clear();

	// # Clear special character
	File::Formatter( content );

	return content; 
}

void File::Formatter(std::string& content){

	std::string tmpCopy;
	uint32_t p1 = 0;

	while( content[ p1 ] != '\0' ){

		if( content[ p1 ] != '\t' ){

			tmpCopy.push_back( content[ p1 ] );
		}

		++p1;
	}

	content = tmpCopy;
	tmpCopy.clear();
}

bool File::Writer(char* path, std::string content){

	
	std::fstream fileHandle;

	fileHandle.open(File::GetFileName(path)+".exec", std::ios::out);

	if( fileHandle.is_open() && fileHandle.good() ){

		fileHandle << content;
	}else{

		fileHandle.close();
		return false;
	}

	fileHandle.close();

	return true;
}