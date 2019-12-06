
main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

clean: 
	rm *.o main

run: 
	./main

