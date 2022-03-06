//#############################
//#  
//#  PROJECT DEVELOPED FOR 
//#  GRADUATED THESES
//#  
//#  @AUTHOR: ESTENIO GARCIA
//#  LICENSE: MIT
//#  
//#############################

#ifdef _WIN32

#include <windows.h>

#else

#define ERROR 	"\033[31"
#define SUCCESS "\033[32"
#define WARNING "\033[33"
#define INFORMATION "\033[36"
#define DEFAULT "\033[0"
	
#endif

#include <iostream>

namespace Console{

	void Print(uint8_t type, std::string msg);
};