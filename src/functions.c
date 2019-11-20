#include <math.h>
#include <stdio.h>
#include "functions.h"
#include "structures.h"


int find_neighbors(transmitter *head, int radius) {
	transmitter *primary = head, *secondary = head;
	/*
	int count = 0;
	*/
	double distance = 0;

	while(primary) {
		while(1) {
			if(!secondary) {
				secondary = head;
				break;
			}

			distance = sqrt((primary->x - secondary->x) * (primary->x - secondary->x) +
					(primary->y - secondary->y) * (primary->y - secondary->y));
			if(distance < (2 * radius)) {
				if(distance == 0) {
					secondary = secondary->next;
					continue;
				}
				/*
				printf("%d to %d: %lf\n", primary->id, secondary->id, distance);
				count++;
				*/
				push_neighbor(primary, secondary);
			}

			secondary = secondary->next;

		}	
		primary = primary->next;
		/*
		printf("------\n");
		*/
	}

	return 1;
}
