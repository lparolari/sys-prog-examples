SHELL=/bin/bash

CC=gcc

OBJECTS=esempiofork.o
SRCS=esempiofork.c
EXECS=esempiofork

all: esempiofork docs

#target "helloworld" richiede $(OBJECTS) per compilare
esempiofork: $(OBJECTS)
	$(CC) -o $@ $<

#target "helloworld.o" richiede $(SRCS) per creare i file oggetto
esempiofork.o: $(SRCS)
	$(CC) -c -o $@ $<

docs: ; doxygen

#target "clean" pulisce i file oggetto e il binario nella directory corrente 
clean: ; rm -rf $(OBJECTS) $(EXECS) docs
