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

int add_neighbor(transmitter *trans, transmitter *neighbor) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));

	if(!temp) {
		printf(ERROR_2);
		return 0;
	}

	temp->data = neighbor;
	temp->next = trans->neighbor_head;
	trans->neighbor_head = temp;

	return 1;
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
	stack_node *hopper = trans->neighbor_head;
	while(hopper) {
		printf("Popped neighbor: %d of %d - %d\n", hopper->data->id, trans->id, hopper->data->frequency);
		hopper = hopper->next;
	}
}
