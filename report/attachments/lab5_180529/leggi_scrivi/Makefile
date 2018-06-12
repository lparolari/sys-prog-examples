CC=gcc

all: leggi scrivi docs

leggi: leggi.o
scrivi: scrivi.o
docs: ; mkdir -p docs; doxygen

clean: ; rm -fr leggi.o leggi scrivi.o scrivi docs