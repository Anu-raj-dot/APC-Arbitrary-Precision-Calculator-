#include "apc.h"
#include "common.h"

/* Function to create operand nodes */
int operand_node(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[], Data *data)
{
	int i = 0;
	int val = 0;
	while (argv[1][i]) // create first operand nodes
	{
		if (argv[1][i] == '-')
		{
			data->operand1_sign = 1; // Set sign for first operand is -ve
			i++;
			val = 1;
			continue;
		}

		Dlist *new = malloc(sizeof(Dlist));
		if (new == NULL)
		{
			printf("ERROR : New node is not created.\n");
			return FAILURE;
		}
		new->data = argv[1][i] - '0'; // Convert char to int
		new->next = NULL;
		new->prev = NULL;

		if (*head1 == NULL)
		{
			*head1 = new;
			*tail1 = new;
		}
		else
		{
			(*tail1)->next = new;
			new->prev = *tail1;
			*tail1 = new;
		}
		i++;
	}
	data->operand1_size = i - val;
	remove_zeros(head1, &data->operand1_size); // Remove leading zeros from first operand

	i = 0, val = 0;
	while (argv[3][i]) // create second operand nodes
	{
		if (argv[3][i] == '-')
		{
			data->operand2_sign = 1; // Set sign for second operand is -ve
			i++;
			val = 1;
			continue;
		}
		Dlist *new = malloc(sizeof(Dlist));
		if (new == NULL)
		{
			printf("ERROR : New node is not created.\n");
			return FAILURE;
		}
		new->data = argv[3][i] - '0'; // Convert char to int
		new->next = NULL;
		new->prev = NULL;

		if (*head2 == NULL)
		{
			*head2 = new;
			*tail2 = new;
		}
		else
		{
			(*tail2)->next = new;
			new->prev = *tail2;
			*tail2 = new;
		}
		i++;
	}
	data->operand2_size = i - val;
	remove_zeros(head2, &data->operand2_size); // Remove leading zeros from second operand

	return SUCCESS;
}

/* Function to print the linked list */
void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
		while (head)
		{
			/* Printing the list */
			if (head->data == 45) // ascii of -
				printf("%c", head->data);
			else
				printf("%d", head->data);

			/* Travering in forward direction */
			head = head->next;
		}
	}
	printf("\n");
}

/* Function to swap two linked lists */
void Swap(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Data *data)
{
	Dlist *temp = *head1; // swap head pointers
	*head1 = *head2;
	*head2 = temp;

	temp = *tail1;
	*tail1 = *tail2;
	*tail2 = temp;

	int value = data->operand1_size; // update operand sizes
	data->operand1_size = data->operand2_size;
	data->operand2_size = value;

	data->swap = 1; // set swap flag to indicate that operands were swapped
}

/* Function to insert a new node at the beginning of the result list */
int insert_first(Dlist **res_head, Dlist **res_tail, int sum)
{
	Dlist *new = malloc(sizeof(Dlist));
	if (new == NULL)
	{
		printf("ERROR : New node is not created.\n");
		return FAILURE;
	}
	new->next = NULL;
	new->prev = NULL;
	new->data = sum;

	if (*res_tail == NULL) // If the result list is empty
	{
		*res_head = new;
		*res_tail = new;
	}
	else
	{
		(*res_head)->prev = new;
		new->next = *res_head;
		*res_head = new;
	}
	return SUCCESS;
}

/* Function to remove leading zeros from a linked list */
int remove_zeros(Dlist **head, data_t *value)
{
	Dlist *temp = *head;
	while (temp->data == 0 && temp->next != NULL)
	{
		*head = temp->next;
		free(temp);
		temp = *head;
		temp->prev = NULL;
		(*value)--;
	}
	return SUCCESS;
}

/* Function to delete a linked list */
int delete_list(Dlist **head, Dlist **tail)
{
	if (*head == NULL) // check list is empty
	{
		return FAILURE;
	}

	while (*head != NULL) // run loop untill head becomes null
	{
		if (*head == *tail) // check if one node is present in list
		{
			*head = NULL; // assign head and tail with null and free that node
			free(*tail);
			*tail = NULL;
		}
		else
		{
			Dlist *temp = *tail;  // add tail value to temporary pointer
			*tail = temp->prev;	  // add last node's previous to tail
			(*tail)->next = NULL; // make previous node's next as null
			free(temp);			  // free last node
		}
	}

	return SUCCESS;
}