CC=gcc

all: read_and_skip docs

read_and_skip: read_and_skip.o
docs: ; mkdir -p docs; doxygen

clean: ; rm -fr read_and_skip.o read_and_skip docs