#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_loader.h"
#include "constants.h"
#include "structures.h"

#define MAX_LINE_LENGTH 80
#define FREQUENCY_STRING "Available frequencies:"
#define RADIUS_STRING "Transmission radius:"
#define TRANSMITTER_STRING "Transmitters:"

file *load_file(char *file_name) {
	char line[MAX_LINE_LENGTH];
	int id = -1, freq = -1, radius = -1;
	/* possibly double needed */
	float x, y;
	FILE* f;
	frequency *head = NULL, *last = NULL;
	transmitter *hlava = NULL , *posledni = NULL;
	file *out = (file*) malloc(sizeof(file));

	if (!(f = fopen(file_name, "r"))) {
		printf(ERROR_4);
		return 0;
	}

	while (fgets(line, MAX_LINE_LENGTH, f)) {

		/* bude fungovat pouze pokud jsou oddily serazene freq -> radius -> transmitter
		 * = mozna lepsi reseni?
		 */

		/* either sizeof - 1 or add \r\n / \n to the *_STRING constants
		 * for \r\n / \n platform check is needed -> sizeof - 1 better
		 */
		if (!strncmp(FREQUENCY_STRING, line, sizeof(FREQUENCY_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d %d", &id, &freq) == 2) {
					if(!head) {
						head = last;
					}
					last = add_frequency(last, id, freq);
					/*
					printf("Loading freq: %d %d\n", id, freq);
					*/
				} else {
					/* test for */
					break;
				}
			}
		}

		if (!strncmp(RADIUS_STRING, line, sizeof(RADIUS_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d", &radius) == 1) {
					/*
					printf("Loading radius: %d\n", radius);
					*/
					out->radius = radius;
				} else {
					/* test for freq/ transmitter */
					break;
				}
			}
		}

		if (!strncmp(TRANSMITTER_STRING, line, sizeof(TRANSMITTER_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d %f %f", &id, &x, &y) == 3) {
					if(!hlava) {
						hlava = posledni;
					}
					posledni = add_transmitter(posledni, id, x, y);
					/*
					printf("Loading transmitter: %d %f %f\n", id, x, y);
					*/
				} else {
					/* test for other types */
					break;
				}
			}
		}
	}

	/*
	print_freq(head);
	print_tran(hlava);
	*/
	out->frequency_head = head;
	out->transmitter_head = hlava;

	return out;
}
