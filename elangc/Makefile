#Detect OS
UNAME = `uname`

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:	./Source/*.cpp
	g++ ./Source/*.cpp -std=c++17 -o ./Bin/elc

Windows_NT:	./Source/*.cpp
	g++ ./Source/*.cpp -std=c++17 -o ./Bin/elc.exe

