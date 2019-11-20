#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "file_loader.h"
#include "structures.h"
#include "constants.h"

int main(int argc, char *argv[]) {	
	transmitter *popper;

	if (argc < 2) {
		printf(ERROR_1);
		return 1;
	}

	if (argc > 2) {
		printf(ERROR_5);
		return 1;
	}

	file *strucs = load_file(argv[1]);

	print_freq(strucs->frequency_head);
	print_tran(strucs->transmitter_head);
	printf("Radius: %d\n", strucs->radius);
	printf("Starting finding neihgbors.\n");
	find_neighbors(strucs->transmitter_head, strucs->radius);
	printf("Finished finding neighbors.\n");

	popper = strucs->transmitter_head;
	while(popper) {
		print_neighbors(popper);
		popper = popper->next;
	}

	print_tran(strucs->transmitter_head);

	return 0;
}
