CXXFLAGS=-std=c++14
main: main.o basics.o advanced.o
	g++ -o main main.o basics.o advanced.o

main.o: main.cpp basics.h advanced.h
	g++ $(CXXFLAGS) -c main.cpp

basics.o: basics.cpp basics.h
	g++ $(CXXFLAGS) -c basics.cpp

advanced.o:advanced.cpp advanced.h
	g++ $(CXXFLAGS) -c advanced.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g

debug: main

clean:
	rm -f main.o basics.o advanced.o main

run:
	./main
