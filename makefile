main: mtrx.o
	g++ -std=c++17 -O3 -fopenmp -Wall -pedantic main.cpp -o main -lopenblas 

mtrx:
	g++ -std=c++17 -fopenmp main.cpp -c	

clean: 
	rm -f *.o main

