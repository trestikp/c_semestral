#ifndef _STRUCTURES_H
#define _STRUCTURES_H

typedef struct the_frequency {
	int id;
	int value;
	struct the_frequency *next;
} frequency;

struct the_stack_node;

typedef struct the_transmitter {
	int id;
	float x, y;
	struct the_stack_node *neighbor_top;
	int neighbor_count;
	struct the_transmitter *next;
} transmitter;

typedef struct the_stack_node {
	transmitter *data;
	struct the_stack_node *next;	
} stack_node;

typedef struct the_file {
	frequency *frequency_head;
	transmitter *transmitter_head;
	int radius;
} file;

frequency *add_frequency(frequency *last, int id, int value);
transmitter *add_transmitter(transmitter *last, int id, float x, float y);
void push_neighbor(transmitter *main, transmitter *neighbor);
transmitter *pop_neighbor(transmitter **main);

void print_freq(frequency *head);
void print_tran(transmitter *head);
void print_neighbors(transmitter *trans);

#endif
