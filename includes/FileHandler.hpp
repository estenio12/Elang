//#############################
//#  
//#  PROJECT DEVELOPED FOR 
//#  GRADUATED THESES
//#  
//#  @AUTHOR: ESTENIO GARCIA
//#  LICENSE: MIT
//#  
//#############################

#pragma once

#include <fstream>
#include <cstring>
#include <iostream>

#include "../includes/Console.hpp"

namespace File{

	std::string GetFileName(char* path);
	std::string Reader(char* path);
	void Formatter(std::string& content);
	bool Writer(char* path, std::string content);
};