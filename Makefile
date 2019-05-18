#############################
###### VARIABLES
#############################

### FLAGS
CXX 		:= g++
CXXFLAGS 	:= -std=c++14 -Wall

### DIRECTORIES
SRCDIR 		:= src
BUILDIR 	:= build
TESTDIR 	:= tests

### FILES
SRCS 		:= $(shell find $(SRCDIR) -type f -name *.cpp)
OBJS 		:= $(patsubst $(SRCDIR)/%,$(BUILDIR)/%,$(SRCS:.cpp=.o))
EXEC 		:= statistical_calculator

### TESTING
TSRCS 		:= src/basics.cpp src/correlation.cpp src/hypTest.cpp src/cInterval.cpp
TESTEXEC    := test_calculator

#############################
###### COMPILING
#############################

$(EXEC): $(OBJS)
	@echo 'Linking and creating executable...'
	@$(CXX) -o $@ $^
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'Calculator is ready to be debugged.',\
		@echo 'Calculator is ready to launch.')
	@echo 'Start using the calculator by typing "make run".'

$(BUILDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDIR) 
	$(if $(findstring g,$(CXXFLAGS)),\
		@echo 'Generating debugging information for $@',\
		@echo 'Compiling object -> $@')
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo 'Success!'

run:
	@echo 'Launching...'
	@./$(EXEC)


#############################
###### DEBUGGING
#############################
debug: CXXFLAGS := $(CXXFLAGS) -g # -fsanitize=address,undefined

debug: $(EXEC)


#############################
###### TESTING
#############################
test: $(TESTDIR)/tests.cpp $(TSRCS)
	@echo 'Testing project...'
	@$(CXX) $(CXXFLAGS) -o $(TESTEXEC) $^
	@echo 'Results can now be viewed by typing "make runtests".'

runtests:
	@echo 'Displaying test results...'
	@./test_calculator



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
	@echo 'Removing build directory and main executable...'
	@$(RM) -r $(BUILDIR) $(EXEC)
	@echo 'Done!'
