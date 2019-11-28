#include <math.h>
#include <stdio.h>
#include "functions.h"
#include "structures.h"
#include "constants.h"


int find_neighbors(transmitter *head, int radius) {
	transmitter *primary = head, *secondary = primary->next;
	double distance = 0;

	/* 
	 * While primary has next count distances from the next transmitter after primary 
	 * (secondary) and ends before last transmitter, which is unneccessary to compare
	 * because of distance 0. Secondary begins on the next transmitter so there is no
	 * need to compare the same transmitters.
	 */
	while(primary->next) {
		while(secondary) {	
			distance = sqrt((primary->x - secondary->x) * (primary->x - secondary->x) +
					(primary->y - secondary->y) * (primary->y - secondary->y));
			if(distance < (2 * radius)) {
				add_neighbor(primary, secondary);
				add_neighbor(secondary, primary);
			}

			secondary = secondary->next;

		}	
		
		primary = primary->next;
		secondary = primary->next;
	}

	return 1;
}

void reset_used_freq(frequency *freq_head) {
	while(freq_head) {
		freq_head->used = 0;
		freq_head = freq_head->next;
	}
}

int find_available_frequency(transmitter *trans, frequency *freq_head) {
	/*stack_node  *neigh_hopper = trans->neighbor_top;
	 */
	stack_node *neighbor = trans->neighbor_head;
	frequency *freq_hopper = freq_head;

//	printf("trans %d\n", trans->id);
	/* find frequencies used by neighbors */
	while(neighbor) {
		/* if neighbor doesn't have frequency jump to next */
		/*
		if(neigh_hopper->data->frequency == -1) {
			neigh_hopper = neigh_hopper->next;
			continue;
		}

		while(freq_hopper) {
			if(neigh_hopper->data->frequency == freq_hopper->value) {
				freq_hopper->used = 1;
				break;
			}

			freq_hopper = freq_hopper->next;
		}

		freq_hopper = freq_head;
		neigh_hopper = neigh_hopper->next;
		*/
		if(neighbor->data->frequency == -1) {
			continue;
		}

//		printf("neigbor %d\n", neihbor->id);
		while(freq_hopper) {
			if(neighbor->data->frequency == freq_hopper->value) {
//				printf("freq %d\n", freq_hopper->value);
				freq_hopper->used = 1;
				break;
			}

			freq_hopper = freq_hopper->next;
		}

		freq_hopper = freq_head;
		neighbor = neighbor->next;
	}

	/* goes through frequency llist and returns frequency of the first unused frequency */
	while(freq_hopper) {
		if(!freq_hopper->used) {
			reset_used_freq(freq_head);
			return freq_hopper->value;
		}

		freq_hopper = freq_hopper->next;
	}

	print_neighbors(trans);
	printf("No suitable frequency found\n");

	return -1;
}

int assign_frequencies(transmitter *trans_head, frequency *freq_head) {
	transmitter *hopper = trans_head;
	int freq;

	while(hopper) {
		/* skip to next transmitter because current already has frequency assigned */
		if(hopper->frequency != -1) {
			hopper = hopper->next;
			continue;
		}

		freq = find_available_frequency(hopper, freq_head);

		if(freq == -1) {
			printf(ERROR_3);
			/* DO MEMORY FREEING */
			return 0;
		}

		hopper->frequency = freq;
		hopper = hopper->next;
	}

	return 1;
}

void print_result(transmitter *head) {
	while(head) {
		printf("%d %d\n", head->id, head->frequency);
		head = head->next;
	}
}
