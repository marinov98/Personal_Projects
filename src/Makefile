######################################################
##### VARIABLES
#######################################################
CXX 		:= g++
CXXFLAGS 	:= -std=c++14 -Wall
SRCS		:= basics.cpp hypTest.cpp cInterval.cpp correlation.cpp # $(wildcard *.cpp)
HDRS        	:= $(patsubst %.cpp,%.hpp, $(SRCS))
OBJS		:= $(patsubst %.cpp,%.o, $(SRCS))
EXEC		:= statistical_calculator
#######################################################


##########################
#### COMPILING & RUNNING
##########################
../$(EXEC): main.o $(OBJS)
	@echo 'Linking objects and building executable...'
	@$(CXX) -o $@ $^
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'Calculator is ready to be debugged',\
		@echo 'Calculator is ready to launch')

main.o: main.cpp $(HDRS)
	@echo 'Compiling main object file..'
	@$(CXX) $(CXXFLAGS) -c main.cpp
	@echo 'Success!'

%.o: %.cpp %.hpp
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'Generating debugging information for $@',\
		@echo 'Compiling object -> $@')
	@$(CXX) $(CXXFLAGS) -c $<
	@echo 'Success!'

run:
	@echo 'Launching...'
	../$(EXEC)

#@cd .. && ./$(EXEC)

##########################
#### DEBUGGING
##########################
debug: CXXFLAGS := $(CXXFLAGS) -g # -fsanitize=address,undefined
	
debug: ../$(EXEC)

##########################
#### CLEANING
##########################
.PHONY: clean

clean:
	@echo 'removing object files and executables...'
	@$(RM) ../$(EXEC) *.o
	@echo 'Done!'

