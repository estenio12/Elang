Compiling:	./sources/*.cpp  ./sources/generator/*.cpp ./sources/lexer/*.cpp ./sources/parser/*.cpp
	clang++ ./sources/*.cpp ./sources/generator/*.cpp ./sources/lexer/*.cpp ./sources/parser/*.cpp -std=c++17 -o ./bin/elc
	./bin/elc ./test.elang
