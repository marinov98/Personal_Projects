##### VARIABLES
EXEC    := main
#####


all: 
	+$(MAKE) -C src

debug:
	cd src && $(MAKE) debug 

run:
	@echo 'launching..'
	@./main

.PHONY: clean

clean:
	cd src && $(MAKE) clean
