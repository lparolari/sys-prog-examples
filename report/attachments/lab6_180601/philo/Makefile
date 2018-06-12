CC=gcc

all: philo docs

philo: philo.o sem.o
sem: sem.o
docs: ; mkdir -p docs; doxygen

clean: ; rm -fr sem.o sem philo.o philo docs
