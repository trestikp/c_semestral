CC = gcc
PARAMS = -Wall -g

all: clean run

clean:
	rm -f freq

run:
	${CC} ${PARAMS} -o freq src/main.c
