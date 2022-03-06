#include "../includes/Console.hpp"

void Console::Print( uint8_t type, std::string msg ){


	#if _WIN32

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch( type ){

			case 0:

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				std::cout << "SUCCESS: ";
				break;
			case 1:

				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				std::cerr << "ERROR: ";
				break;
			case 2:

				SetConsoleTextAttribute(hConsole, 6);
				std::cout << "WARNING: ";
				break;
			default:

				SetConsoleTextAttribute(hConsole, 3);
				std::cout << "INFORMATION: ";
				break;
		}

		SetConsoleTextAttribute(hConsole, 15);
		std::cout << msg << std::endl;
	#else

		switch( type ){

			case 0:

				std::cout << SUCCESS << "SUCCESS: " << DEFAULT << msg << std::endl;
				break;
			case 1:

				std::cerr << ERROR << "ERROR: " << DEFAULT << msg << std::endl;
				break;
			case 2:

				std::cout << WARNING << "WARNING: " << DEFAULT << msg << std::endl;
				break;
			default:

				std::cout << INFORMATION << "INFORMATION: " << DEFAULT << msg << std::endl;
				break;
		}

	#endif
}