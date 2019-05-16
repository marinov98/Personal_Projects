##### VARIABLES
EXEC    := statistical_calculator
#####


all: 
	+$(MAKE) -C src

debug:
	cd src && $(MAKE) debug 

run:
	@echo 'launching..'
	@./$(EXEC)

.PHONY: clean

clean:
	cd src && $(MAKE) clean
