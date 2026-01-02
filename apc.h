#ifndef APC_H
#define APC_H

#define SUCCESS 1
#define FAILURE 0
#define ZERO_ERROR -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;
typedef struct node // Node structure for double linked list
{
	struct node *prev;
	data_t data;
	struct node *next;
} Dlist;

typedef struct // Data structure for operand sizes and result size
{
	data_t operand1_size;
	data_t operand2_size;
	data_t result_size;
	data_t operand1_sign;
	data_t operand2_sign;
	data_t swap; 
} Data;

// Function Prototypes
int validate_args(int argc, char *argv[], char *ch);
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
#endif
