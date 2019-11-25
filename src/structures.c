#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "constants.h"

frequency *add_frequency(frequency *last, int id, int value) {
	frequency *temp = (frequency*) malloc(sizeof(frequency));

	if(!temp) {
		printf(ERROR_2);
		/* Exit code? */
		return NULL;
	}

	temp->id = id;
	temp->value = value;
	temp->used = 0;
	
	if(!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

transmitter *add_transmitter(transmitter *last, int id, float x, float y) {
	transmitter *temp = (transmitter*) malloc(sizeof(transmitter));

	if(!temp) {
		printf(ERROR_2);
		return NULL;
	}
	
	temp->id = id;
	temp->x = x;
	temp->y = y;
	temp->frequency = -1;

	if(!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

void push_neighbor(transmitter *main, transmitter *neighbor) {	
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));

	if(!temp) {
		printf(ERROR_2);
		return;
	}

	temp->data = neighbor;
	temp->next = main->neighbor_top;
	main->neighbor_top = temp;
}

transmitter *pop_neighbor(transmitter **main) {
	if(!(*main)->neighbor_top) {
		return (transmitter*) NULL;
	}

	stack_node *temp = (*main)->neighbor_top;
	(*main)->neighbor_top = (*main)->neighbor_top->next;
	transmitter *popped = temp->data;
	free(temp);

	return popped;
}

void print_freq(frequency *head) {
	while(head) {
		printf("Frequency: %d %d\n", head->id, head->value);
		head = head->next;
	}
}

void print_tran(transmitter *head) {
	while(head) {
		printf("Transmitter: %d %f %f\n", head->id, head->x, head->y);
		head = head->next;
	}
}

void print_neighbors(transmitter *trans) {
	transmitter *popped = NULL;
	while(trans->neighbor_top) {
		popped = pop_neighbor(&trans);
		printf("Popped neighbor: %d of %d - %d\n", popped->id, trans->id, trans->frequency);
	}
}
