test src/*.cpp:
	g++ -std=c++23 src/*.cpp -g -o unilang.o
	./unilang.o
