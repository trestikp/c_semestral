#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "file_loader.h"
#include "structures.h"
#include "constants.h"

#define DESIRED_ARGUMENT_COUNT 2

transmitter *transmitter_head = NULL;
frequency *frequency_head = NULL;
int radius = -1;

void print_help() {
	printf("Use: freq <filename>\n");
	printf("Where <filename> is the file with\n");
	printf("transmitter data\n");
	printf("i.e.: ./freq data/vysilace-25.txt\n");
}

void setup(int argc, char* argv[]) {
	if (argc < DESIRED_ARGUMENT_COUNT) {
		printf(ERROR_1);
		print_help();
		exit(1);
	}

	if (argc > DESIRED_ARGUMENT_COUNT) {
		printf(ERROR_5);
		print_help();
		exit(1);
	}

	if (!load_file(argv[1], &transmitter_head, &frequency_head, &radius))
		exit(1);
}

void run() {
	if(!find_neighbors(transmitter_head, radius))
		return;
	if(!assign_frequencies(transmitter_head, frequency_head))
		return;
	print_result(transmitter_head);
}

void shutdown() {
	free_frequencies(frequency_head);
	free_transmitters(transmitter_head);
}


int main(int argc, char *argv[]) {		
	setup(argc, argv);
	run();
	shutdown();

	return 0;
}
