#ifndef COMMON_H
#define COMMON_H

#include "apc.h"

// Function Prototypes
int operand_node(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[], Data *data);
void print_list(Dlist *head);
void Swap(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Data *data);
int insert_first(Dlist **head, Dlist **tail, int sum);
int remove_zeros(Dlist **head, data_t *value);
int delete_list(Dlist **head, Dlist **tail);

#endif