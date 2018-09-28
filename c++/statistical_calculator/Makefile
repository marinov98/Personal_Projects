CXXFLAGS=-std=c++14
main: main.o basics.o advanced.o correlation.o
	g++ -o main main.o basics.o advanced.o correlation.o

main.o: main.cpp basics.hpp advanced.hpp
	g++ $(CXXFLAGS) -c main.cpp

basics.o: basics.cpp basics.hpp
	g++ $(CXXFLAGS) -c basics.cpp

advanced.o:advanced.cpp advanced.hpp
	g++ $(CXXFLAGS) -c advanced.cpp

correlation.o:correlation.cpp correlation.hpp
		g++ $(CXXFLAGS) -c correlation.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g

debug: main

clean:
	rm -f main.o basics.o advanced.o correlation.o main

run:
	./main
