# Name of the project 
PROJ_NAME=MySearch

# .c files
C_SOURCE=$(wildcard ./source/*.c)

# .h files
H_SOURCE=$(wildcard ./source/*.h)

# .o files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# Compiler and Linker
CC = gcc

# Flags for compiler
CC_FLAGS = -c -Wall

# Compilation and Linking
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo -ne 'Building binary using GCC linker: $@...'
	@ $(CC) $^ -o $@
	@ echo ' Done!'
	@ echo ' '

./objects/%.o: ./source/%.c ./source/%.h
	@ echo -ne 'Building target using GCC compiler: $<...'
	@ $(CC) $< $(CC_FLAGS) -o $@
	@ echo ' Done!'

./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo -ne 'Building target using GCC compiler: $<...'
	@ $(CC) $< $(CC_FLAGS) -o $@
	@ echo ' Done!'

objFolder:
	@ mkdir -p objects

clean:
	@ echo -ne 'Cleanning project...'
	@ rm -rf ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects
	@ echo ' Done!'

.PHONY: all clean