#######################################################
##### VARIABLES
#######################################################
CXX 		:= g++
CXXFLAGS 	:= -std=c++14
SRCS		:= basics.cpp hypTest.cpp cInterval.cpp correlation.cpp #$(wildcard *.cpp)
HDRS        := $(patsubst %.cpp,%.hpp, $(SRCS))
OBJS		:= $(patsubst %.cpp,%.o, $(SRCS))
EXEC		:= main
#######################################################


##########################
#### COMPILING & RUNNING
##########################
$(EXEC): main.o $(OBJS)
	@echo 'building executable...'
	@$(CXX) -o $@ $^
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'Calculator ready to be debugged',\
		@echo 'Calculator ready to launch')

main.o: main.cpp $(HDRS)
	@echo 'building main object file..'
	@$(CXX) $(CXXFLAGS) -c main.cpp
	@echo 'Success!'

%.o: %.cpp %.hpp
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'debugging -> $@',\
		@echo 'building object -> $@')
	@$(CXX) $(CXXFLAGS) -c $<
	@echo 'Success!'

run:
	@echo 'Launching...'
	@./main

##########################
#### DEBUGGING
##########################
debug: CXXFLAGS := $(CXXFLAGS) -g # -fsanitize=address,undefined
	
debug: main

##########################
#### CLEANING
##########################
.PHONY: clean

clean:
	@echo 'removing object files and executables...'
	@$(RM) $(EXEC) *.o
	@echo 'Done!'

