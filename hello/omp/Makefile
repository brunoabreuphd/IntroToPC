# GCC compiler
CC=g++

# compilation flags (none)
LDFLAGS=-fopenmp

# source file
SOURCE=./hello_omp.cpp

# binary name
EXEC=hello_omp.exe

all:
	$(CC) $(LDFLAGS) $(SOURCE) -o $(EXEC)
	@echo -e "----- COMPILATION DONE -----"

clean:
	rm -r $(EXEC)

