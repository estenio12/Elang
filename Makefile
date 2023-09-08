Compiling:	./sources/*.cpp  ./sources/generator/*.cpp ./sources/lexer/*.cpp ./sources/parser/*.cpp
	g++ ./sources/*.cpp ./sources/generator/*.cpp ./sources/lexer/*.cpp ./sources/parser/*.cpp -std=c++17 -o ./bin/elc
	./bin/elc ./test.elang
