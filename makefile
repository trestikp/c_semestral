CC = gcc
PARAMS = -Wall -g -lm

all: clean run remove_o

clean:
	rm -f freq

file_loader:
	${CC} ${PARAMS} -c src/file_loader.c src/file_loader.h src/constants.h

structures:
	${CC} ${PARAMS} -c src/structures.c src/structures.h src/constants.h

functions:
	${CC} ${PARAMS} -c src/functions.c src/functions.h

run: structures file_loader functions
	${CC} ${PARAMS} -o freq src/main.c structures.o file_loader.o  functions.o

remove_o:
	rm *.o
