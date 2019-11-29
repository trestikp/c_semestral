#include "structures.h"

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

int find_neighbors(transmitter *head, int radius);
int assign_frequencies(transmitter *trans_head, frequency *freq_head);
int free_transmitters(transmitter *head);
int free_frequencies(frequency *head);
void print_result(transmitter *head);

#endif
