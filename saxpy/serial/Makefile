# Fortran GCC compiler
CC=gcc

# compilation flags (none)
LDFLAGS=

# source file
SOURCE=./saxpy_serial.c

# binary name
EXEC=saxpy_serial.exe

all:
	$(CC) $(LDFLAGS) $(SOURCE) -o $(EXEC)
	@echo -e "----- COMPILATION DONE -----"


clean:
	rm -r $(EXEC)

