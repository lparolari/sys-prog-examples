SHELL=/bin/bash

CC=gcc

OBJECTS=esempiofork.o
SRCS=esempiofork.c

#target "helloworld" richiede $(OBJECTS) per compilare
esempiofork: $(OBJECTS)
	$(CC) -o $@ $<

#target "helloworld.o" richiede $(SRCS) per creare i file oggetto
esempiofork.o: $(SRCS)
	$(CC) -c -o $@ $<

#target "clean" pulisce i file oggetto e il binario nella directory corrente 
clean: rm -f helloworld helloworld.o

#target "clean" non è un file!
.PHONY: clean
