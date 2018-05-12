CXXFLAGS=-std=c++14
main: main.o basics.o
	g++ -o main main.o basics.o

main.o: main.cpp basics.h
	g++ $(CXXFLAGS) -c main.cpp

basics.o: basics.cpp basics.h
	g++ $(CXXFLAGS) -c basics.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g
	
debug: main

clean:
	rm -f main.o basics.o main 

run:
	./main
