CXXFLAGS=-std=c++14
main: main.o basics.o cInterval.o hypTest.o correlation.o
	g++ -o main main.o basics.o cInterval.o hypTest.o correlation.o

main.o: main.cpp basics.hpp cInterval.hpp hypTest.hpp
	g++ $(CXXFLAGS) -c main.cpp

hypTest.o: hypTest.cpp hypTest.hpp
	g++ $(CXXFLAGS) -c hypTest.cpp

basics.o: basics.cpp basics.hpp
	g++ $(CXXFLAGS) -c basics.cpp

cInterval.o:cInterval.cpp cInterval.hpp
	g++ $(CXXFLAGS) -c cInterval.cpp

correlation.o:correlation.cpp correlation.hpp
		g++ $(CXXFLAGS) -c correlation.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g

debug: main

clean:
	rm -f main.o basics.o cInterval.o correlation.o hypTest.o main

run:
	./main
