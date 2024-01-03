Compiling:	./sources/*.cpp 
	g++ -g ./sources/*.cpp -std=c++20 -static-libgcc -o ./bin/elang 
	./bin/elang ./bin/quiz.elang quiz.cpp
