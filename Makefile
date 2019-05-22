#############################
###### VARIABLES
#############################

### FLAGS 
CXX 		:= g++
STANDARD 	:= -std=c++14 $(CXXFLAGS)
WARNINGS 	:= -fdiagnostics-color=always -Wall -Wextra #-Wconversion

### DIRECTORIES
SRCDIR 		:= src
BUILDIR 	:= build
TESTDIR 	:= tests

### FILES
SRCS 		:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJS 		:= $(patsubst $(SRCDIR)/%,$(BUILDIR)/%,$(SRCS:.cpp=.o))
EXEC 		:= statistical_calculator

### UNIT TESTING
TSRCS 		:= src/basics.cpp src/correlation.cpp src/hypTest.cpp src/cInterval.cpp
TESTEXEC        := test_calculator

#############################
###### COMPILING  
#############################

$(EXEC): $(OBJS)
	@echo 'Linking and creating executable...'
	@$(CXX) $(STANDARD) $(WARNINGS) -o $@ $^
	$(if $(findstring g,$(STANDARD)),\
		@echo 'Calculator is ready to be debugged.',\
		@echo 'Calculator is ready to launch.')

$(BUILDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDIR) 
	$(if $(findstring g,$(STANDARD)),\
		@echo 'Generating debugging information for $@',\
		@echo 'Compiling object -> $@')
	@$(CXX) $(STANDARD) $(WARNINGS) -c -o $@ $<
	@echo 'Success!'


#############################
###### RUNNING
#############################

### 1 argument

run:
	@echo 'Launching...'
	@./$(EXEC)
	@echo 'use "make clean" to clean build directory and executable'

### 2 argument

parse:
	@echo 'reading data.txt...'
	@echo 'calculating...'
	@./$(EXEC) data.txt

### 3 argument

mean:
	@echo 'Command "MEAN" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt MEAN

median:
	@echo 'Command "MEDIAN" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt MEDIAN

percentile:
	@echo 'Command "PERCENTILE" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt PERCENTILE

mode:
	@echo 'Command "MODE" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt MODE
	
range:
	@echo 'Command "RANGE" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt RANGE

min:
	@echo 'Command "MIN" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt MIN

max:
	@echo 'Command "MAX" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt MAX

outliers:
	@echo 'Command "OUTLIERS" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt OUTLIERS

sd:
	@echo 'Command "SD(standard deviation)" detected.'
	@echo 'calculating...'
	@./$(EXEC) data.txt SD

#############################
###### DEBUGGING
#############################

debug: STANDARD := $(STANDARD) -g -fsanitize=address,undefined

debug: $(EXEC)


#############################
###### TESTING
#############################

test: $(TESTDIR)/tests.cpp $(TSRCS)
	@echo 'Testing project...'
	@$(CXX) $(STANDARD) $(WARNINGS) -o $(TESTEXEC) $^
	@echo 'Results can now be viewed by typing "make runtests".'

runtests:
	@echo 'Displaying test results...'
	@./test_calculator
	@echo 'clean with "make cleantests"'



#############################
###### CLEANING
#############################

.PHONY: cleanall cleantests clean

cleanall:
	@echo 'Removing build directories, objects, and executables...'
	@$(RM) -r $(BUILDIR) $(EXEC) $(TESTEXEC)
	@echo 'Project has been cleaned.'	

cleantests:
	@echo 'removing test executable...'
	@$(RM) $(TESTEXEC)
	@echo 'Done!'

clean: 
	@echo 'Removing build directory and executable...'
	@$(RM) -r $(BUILDIR) $(EXEC)
	@echo 'Done!'
