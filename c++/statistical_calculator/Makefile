
CXX 		:= g++
CXXFLAGS 	:= $(CXXFLAGS) -std=c++14
SRCS		 = $(wildcard *.cpp) 
OBJS		:= $(patsubst %.cpp,%.o, $(SRCS))
EXEC		:= main

$(EXEC): $(OBJS)
	@echo 'building executable...'
	@$(CXX) -o $@ $^
	@echo 'Calculator ready to launch'

%.o: %.cpp %.hpp
	@echo 'building object -> $@ ...'
	@$(CXX) $(CXXFLAGS) -c $<
	@echo 'Success!'

debug: CXXFLAGS:=$(CXXFLAGS) -g # -fsanitize=address,undefined

debug: main

.PHONY: clean

clean:
	@echo 'removing object files and executables...'
	@$(RM) $(EXEC) $(OBJS)
	@echo 'Done!'

run:
	./main
