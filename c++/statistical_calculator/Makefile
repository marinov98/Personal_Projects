CXXFLAGS=-std=c++14
main: main.o basics.o confidence.o
	g++ -o main main.o basics.o confidence.o

main.o: main.cpp basics.h confidence.h
	g++ $(CXXFLAGS) -c main.cpp

basics.o: basics.cpp basics.h
	g++ $(CXXFLAGS) -c basics.cpp

confidence.o:confidence.cpp confidence.h
	g++ $(CXXFLAGS) -c confidence.cpp

debug: CXXFLAGS:=$(CXXFLAGS) -g

debug: main

clean:
	rm -f main.o basics.o confidence.o main

run:
	./main
