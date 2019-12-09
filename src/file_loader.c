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

/*
 *	file *load_file(char *file_name) {
 *	
 *	Loads file
 *	
 *	Returns *file on success
 *		NULL on error.
 */
int load_file(char *file_name, transmitter **transmitter_head,
	      frequency **frequency_head, int *rad) {
	char line[MAX_LINE_LENGTH];
	int id = -1, freq = -1, radius = -1;
	/* possibly double needed */
	float x = 0, y = 0;
	FILE *f = NULL;
	frequency *f_last = NULL;
	transmitter *t_last = NULL;
	/* failed to open file */

	if (!(f = fopen(file_name, "r"))) {
		printf(ERROR_4);
		return 0;
	}

	while (fgets(line, MAX_LINE_LENGTH, f)) {

		/* either sizeof - 1 or add \r\n / \n to the 
		 * *_STRING constants
		 * for \r\n / \n platform check is needed
		 * -> sizeof - 1 better
		 */
		if (!strncmp(FREQUENCY_STRING, line,
		    sizeof(FREQUENCY_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d %d", &id, &freq) == 2) {
					if(!(*frequency_head)) {
						*frequency_head = f_last;
					}
					f_last = add_frequency(f_last,
							       id, freq);
					if (!f_last)
						return 0;
												
				} else {
					/* if sscanf doesn't load line
					 * correctly breakes inner while
					 * and moves to next block
					 */
					break;
				}
			}
		}

		if (!strncmp(RADIUS_STRING, line, sizeof(RADIUS_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d", &radius) == 1) {
					*rad = radius;
				} else {
					/* same as above */
					break;
				}
			}
		}

		if (!strncmp(TRANSMITTER_STRING, line,
	 	    sizeof(TRANSMITTER_STRING) - 1)) {
			while (fgets(line, MAX_LINE_LENGTH, f)) {
				if (sscanf(line, "%d %f %f", &id, &x, &y) == 3)
				{
					if (!(*transmitter_head)) {
						*transmitter_head = t_last;
					}
					t_last = add_transmitter(t_last,
								 id, x, y);	
					if (!t_last)
						return 0;
				} else {
					break;
				}
			}
		}
	}

	fclose(f);

	return 1;
}
