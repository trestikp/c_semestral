CC = gcc
PARAMS = -Wall -g

all: clean run remove_o

clean:
	rm -f freq

file_loader:
	${CC} ${PARAMS} -c src/file_loader.c src/file_loader.h src/constants.h

structures:
	${CC} ${PARAMS} -c src/structures.c src/structures.h src/constants.h

run: structures file_loader
	${CC} ${PARAMS} -o freq src/main.c structures.o file_loader.o 

remove_o:
	rm *.o
