#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "structures.h"
#include "constants.h"

/*
 *	int find_neighbors(transmitter *head, int radius) {
 *
 * 	Function finds neighbors for each transmitter in linked list
 * 	and adds them to their respective neighbor linked list.
 *
 * 	Returns 1 on successful finding of all neighbors
 * 		0 on error (memory allocation).
 */
int find_neighbors(transmitter *head, int radius) {
	transmitter *primary = head, *secondary = primary->next;
	double distance = 0;

	/* 
	 * While primary has next count distances from the next
	 * transmitter after primary (secondary) and ends before
	 * last transmitter, which is unneccessary to compare
	 * because of distance 0. Secondary begins on the next
	 * transmitter so there is no need to compare the same transmitters.
	 */
	while (primary->next) {
		while (secondary) {	
			distance = sqrt((primary->x - secondary->x) *
					(primary->x - secondary->x) +
					(primary->y - secondary->y) *
					(primary->y - secondary->y));
			if (distance < (2 * radius)) {
				/* if add_neighbors fails to allocate
				 * memory -> return 0 */
				if (!add_neighbor(primary, secondary))
					return 0;
				if (!add_neighbor(secondary, primary))
					return 0;
			}

			secondary = secondary->next;

		}	
		
		primary = primary->next;
		secondary = primary->next;
	}

	return 1;
}

/*
 *	void reset_used_freq(frequency *freq_head) {
 *
 *	Sets frequencies used to 0 (not used). It is a complimentary
 *	function to frequency assignment.
 */
void reset_used_freq(frequency *freq_head) {
	while (freq_head) {
		freq_head->used = 0;
		freq_head = freq_head->next;
	}
}

/*
 *	int push_neighbors(transmitter *trans, stack_node **root) {
 *
 *	Pushes neighbors of a transmitter that is being assigned frequency.
 *	Complimentary function to frequency assignment.
 *
 *	Returns 1 on success
 *		0 on error (memory allocation)
 */
int push_neighbors(transmitter *trans, stack_node **root) {
	stack_node *hopper = trans->neighbor_head;

	while (hopper) {
		if (hopper->data->frequency == -1 &&
		    !hopper->data->is_in_stack) {
			/* if push failed to allocate memory return 0 */
			if(!push(root, hopper->data))
				return 0;
		}
		hopper = hopper->next;
	}

	return 1;
}

/*
 *	int find_available_frequency(transmitter *trans, frequency *freq_head) {
 *
 * 	Finds available frequency for assignment. First searches all neighbor
 * 	frequencies. If a frequency is used changes its "used" value to 1.
 * 	Then goes through frequency list and returns first unused frequency.
 * 	Complimentary function to frequency assignment.
 *
 * 	Returns frequency value on successful find of unused frequency
 * 		-1 if an available frequency isn't found.
 */
int find_available_frequency(transmitter *trans, frequency *freq_head) {
	stack_node *neighbor = trans->neighbor_head;
	frequency *freq_hopper = freq_head;

	/* find frequencies used by neighbors */
	while (neighbor) {
		/* if neighbor doesn't have frequency jump to next */
		if (neighbor->data->frequency == -1) {
			neighbor = neighbor->next;
			continue;
		}

		while (freq_hopper) {
			if (neighbor->data->frequency == freq_hopper->value) {
				freq_hopper->used = 1;
				break;
			}

			freq_hopper = freq_hopper->next;
		}

		freq_hopper = freq_head;
		neighbor = neighbor->next;
	}

	/* goes through frequency llist and returns frequency
	 * of the first unused frequency */
	while (freq_hopper) {
		if (!freq_hopper->used) {
			reset_used_freq(freq_head);
			return freq_hopper->value;
		}

		freq_hopper = freq_hopper->next;
	}

	return -1;
}

/*
 *	int assign_frequencies(transmitter *trans_head, frequency *freq_head) {
 *
 * 	Goes through transmitter linked list and assigns frequencies to
 * 	transmitters.
 *
 * 	Returns 1 on success
 * 		0 on error.
 */
int assign_frequencies(transmitter *trans_head, frequency *freq_head) {
	transmitter *hopper = trans_head, *popped = NULL;
	stack_node *root = NULL;
	int freq = 0;

	while (hopper) {
		/* if stack is empty */
		if (is_empty(root)) { 
			if (hopper->frequency != -1) {
				hopper = hopper->next;
				continue;
			}

			if (!push(&root, hopper))
				return 0;
		}

		popped = pop(&root);

		if (!push_neighbors(popped, &root))
			return 0;

		freq = find_available_frequency(popped, freq_head); 
		if (freq == -1) {
			printf(ERROR_3);
			return 0;
		}

		popped->frequency = freq;
	}

	return 1;
}

/*
 *	void free_neighbors(transmitter *head) {
 *
 *	Frees nieghbor linked list
 */
void free_neighbors(transmitter *head) {
	/* if neighbor_head is NULL don't do anything
	 * transmitter doesn't have neighbors */
	if (!head->neighbor_head)
		return;

	stack_node *remover = head->neighbor_head;
	stack_node *remover_next = remover->next;

	while (remover_next) {
		free(remover);
		remover = remover_next;
		remover_next = remover->next;
	}
	free(remover);
}

/*
 *	void free_transmitters(transmitter *head) {
 *
 *	Frees transmitter linked list
 */
void free_transmitters(transmitter *head) {
	transmitter *remover = head;

	while (head) {
		remover = head;
		head = head->next;
		free_neighbors(remover);
		free(remover);
	}
}

/*
 *	void free_frequencies(frequency *head) {
 *
 *	Frees frequency linked list
 */
void free_frequencies(frequency *head) {
	frequency *remover = head;

	while (head->next) {
		remover = head;
		head = head->next;
		free(remover);
	}
	free(head);
}

/*
 *	void print_result(transmitter *head) {
 *
 *	Prints the transmitter linked list.
 *	Supposed to be used after assign_frequencies.
 */
void print_result(transmitter *head) {
	while (head) {
		printf("%d %d\n", head->id, head->frequency);
		head = head->next;
	}
}
