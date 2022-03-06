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

#define ERROR 	"\033[31m"
#define SUCCESS "\033[32m"
#define WARNING "\033[33m"
#define INFORMATION "\033[36m"
#define DEFAULT "\033[0m"
	
#endif

#include <iostream>

namespace Console{

	void Print(uint8_t type, std::string msg);
};