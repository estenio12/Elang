#Detect OS
UNAME = `uname`

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:	./main.cpp
	g++ ./main.cpp -std=c++17 -o ./bin/elangc

Windows_NT:	./main.cpp
	g++ ./main.cpp -std=c++17 -o ./bin/elangc.exe

