
CXX 		:= g++
CXXFLAGS 	:= $(CXXFLAGS) -std=c++14
SRCS		:= basics.cpp cInterval.cpp hypTest.cpp correlation.cpp main.cpp
OBJS		:= $(patsubst %.cpp,%.o, $(SRCS))
EXEC		:= main

$(EXEC): $(OBJS)
	@echo 'building executable...'
	$(CXX) -o $@ $^

%.o: %.cpp %.hpp
	@echo 'building object -> $@ ...'
	$(CXX) $(CXXFLAGS) -c $<

debug: CXXFLAGS:=$(CXXFLAGS) -g # -fsanitize=address,undefined

debug: main

.PHONY: clean

clean:
	@echo 'removing object files and executables...'
	$(RM) $(EXEC) $(OBJS)

run:
	./main
