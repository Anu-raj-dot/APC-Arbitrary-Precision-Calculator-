/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
			: data: Pointer to the data structure containing operand sizes and result size.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include "common.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data)
{
	if (data->operand1_sign == 0 && data->operand2_sign == 1) // If second operand is negative, perform addition
	{
		data->operand1_sign = 0;
		data->operand2_sign = 0;
		addition(head1, tail1, head2, tail2, headR, tailR, data);
		return SUCCESS;
	}
	if (data->operand1_sign == 1 && data->operand2_sign == 0) // If first operand is negative, perform addition
	{
		data->operand1_sign = 0;
		data->operand2_sign = 0;
		addition(head2, tail2, head1, tail1, headR, tailR, data);
		insert_first(headR, tailR, 45); // insert -ve sign
		return SUCCESS;
	}
	int neg_flag = 0; // flag to indicate negative result

	Dlist *temp1 = *head1;
	Dlist *temp2 = *head2;

	if (data->operand1_size < data->operand2_size) // swap operand based on length
	{
		Swap(head1, tail1, head2, tail2, data);
		neg_flag = 1;
	}
	else if (data->operand1_size == data->operand2_size) // if both operands are of equal size
	{
		int count = 0;
		while (temp1)
		{
			if (temp1->data > temp2->data) // if first operand is greater
			{
				break;
			}
			else if (temp1->data < temp2->data) // if first operand is smaller
			{
				Swap(head1, tail1, head2, tail2, data);
				neg_flag = 1;
				break;
			}
			else // if both digits are equal
			{
				count++;
				if (count == data->operand1_size)
				{
					insert_first(headR, tailR, 0);
					return SUCCESS;
				}
			}
			temp1 = temp1->next; // move to next node
			temp2 = temp2->next;
		}
	}

	int sub = 0;
	int i = 0;

	temp1 = *tail1; // point to last node of operands
	temp2 = *tail2;

	while (temp1 != NULL || temp2 != NULL) // Run until all digits are processed
	{
		if (temp2 == NULL) // if second operand has ended
		{
			sub = temp1->data;
		}
		else if (temp1->data < temp2->data) // if first operand is smaller
		{
			Dlist *borrow_node = temp1->prev;

			while (borrow_node) // run until borrow_node is not NULL
			{
				if (borrow_node->data == 0) // if borrow_node data is 0, make it 9
				{
					borrow_node->data = 9;
				}
				else // if borrow_node data is not 0, decrement it and break
				{
					borrow_node->data -= 1;
					break;
				}
				borrow_node = borrow_node->prev;
			}
			sub = 10 + temp1->data - temp2->data; // find the difference
		}
		else
		{
			sub = temp1->data - temp2->data; // find the difference
		}

		insert_first(headR, tailR, sub); // insert the difference at the beginning of the resultant list

		data->result_size++; // increment the result size

		temp1 = (temp1 != NULL ? temp1->prev : NULL); // move to next previous node
		temp2 = (temp2 != NULL ? temp2->prev : NULL);
		i++;
	}

	data->operand1_size = i;
	remove_zeros(headR, &data->result_size); // remove leading zeros from the result

	if (neg_flag == 1)
	{
		insert_first(headR, tailR, 45); // insert negative sign for negative result
	}

	if (data->operand1_sign == 1 && data->operand2_sign == 1) // If both operands are negative
	{
		if ((data->operand1_size > data->operand2_size || data->operand1_size == data->operand2_size) && data->swap != 1)
		{
			insert_first(headR, tailR, 45); // insert -ve sign
		}
		else
		{
			Dlist *temp = *headR;
			*headR = temp->next; // move head to next node
			free(temp);
		}
	}
	return SUCCESS;
}