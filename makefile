main: mtrx.h
	g++ -std=c++17 -O3 -fopenmp -Wall -pedantic main.cpp -o main -lopenblas 
	
clean: 
	rm -f *.o main

