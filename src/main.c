#include <stdio.h>
#include <stdlib.h>
#include "file_loader.h"
#include "structures.h"
#include "constants.h"

int main(int argc, char *argv[]) {	

	if (argc < 2) {
		printf(ERROR_1);
		return 1;
	}

	if (argc > 2) {
		printf(ERROR_5);
		return 1;
	}

	load_file(argv[1]);

	return 0;
}
