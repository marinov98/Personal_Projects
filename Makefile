##### VARIABLES
EXEC    := statistical_calculator
#####


all: 
	@echo 'Running application...'
	@echo 'Please wait while calculator is being built...'
	+@$(MAKE) -C src
	@echo 'You may now start the calculator with "make run"'

debug:
	@echo 'Debug mode requested.'
	@echo 'Compiling calculator with debug mode...'
	+@$(MAKE) debug -C src 

run:
	+@$(MAKE) run -C src 

.PHONY: clean

clean:
	+@$(MAKE) clean -C src
#	cd src && $(MAKE) clean
