##### VARIABLES
EXEC    := statistical_calculator
#####


all: 
	+$(MAKE) -C src

debug:
	cd src && $(MAKE) debug 

run:
	@echo 'launching..'
	@./statistical_calculator

.PHONY: clean

clean:
	cd src && $(MAKE) clean
