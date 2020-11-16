# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib

# All Targets
all: sortAlg

# Tool invocations
# Executable "sortAlg" depends on the files bin/main.o  - bin/SortAlgos.o

sortAlg: bin/Main.o bin/SortAlgos.o 

	@echo 'Building target: sortAlg'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/sortAlg bin/Main.o bin/SortAlgos.o  $(LFLAGS)
	@echo 'Finished building target: sortAlg'
	@echo ' '


bin/Main.o: Main.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/Main.o Main.cpp


bin/SortAlgos.o: SortAlgos.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/SortAlgos.o SortAlgos.cpp


#Clean the build directory
clean: 
	rm -f bin/*
