CXXFLAGS=-std=c++14
main: main.o funcs.o
	g++ -o main main.o funcs.o

main.o: main.cpp funcs.h
	g++ $(CXXFLAGS) -c main.cpp

funcs.o: funcs.cpp funcs.h
	g++ $(CXXFLAGS) -c funcs.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g
	
debug: main

tests:tests.cpp funcs.cpp
	g++ $(CXXFLAGS) -o tests $^

clean:
	rm -f main.o funcs.o main tests

run:
	./main
