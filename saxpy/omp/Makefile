# C++ GCC compiler
CC=g++

# compilation flags (none)
LDFLAGS=-fopenmp

# source file
SOURCE=./saxpy_omp.cpp

# binary name
EXEC=saxpy_omp.exe

all:
	$(CC) $(LDFLAGS) $(SOURCE) -o $(EXEC)
	@echo -e "----- COMPILATION DONE -----"


clean:
	rm -r $(EXEC)

