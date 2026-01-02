/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
			: data: Pointer to the Data structure containing operand sizes and result size.
*Output			: Status (SUCCESS / FAILURE)
				: ZERO_ERROR: Division by zero error.
*******************************************************************************************************************************************************************/
#include "apc.h"
#include "common.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data)
{
	int val = data->operand1_sign + data->operand2_sign;
	data->operand1_sign = 0; // Reset operand signs for division
	data->operand2_sign = 0;

	if (data->operand2_size == 1 && (*head2)->data == 0) // Check for division by zero
	{
		return ZERO_ERROR;
	}

	Dlist *temp = *head1;
	Dlist *temp1 = *head2;
	int count = 0;
	while (data->operand1_size == data->operand2_size && temp) // check if both operands are of equal size
	{
		if (temp->data == temp1->data) // if both digits are equal
		{
			count++;
		}
		else if (temp->data > temp1->data) // If first operand is greater
		{
			break;
		}
		else
		{
			insert_first(headR, tailR, 0);
			return SUCCESS;
		}

		if (count == data->operand1_size) // if both operands are equal
		{
			insert_first(headR, tailR, 1);
			return SUCCESS;
		}
		temp = temp->next; // move to next node
		temp1 = temp1->next;
	}

	if (data->operand1_size < data->operand2_size || data->operand1_size == 1 && (*head1)->data == 0) // check for division by zero
	{
		insert_first(headR, tailR, 0);
		return SUCCESS;
	}

	Dlist *temp_head = NULL;
	Dlist *temp_tail = NULL;

	unsigned long long int quotient = 0;
	data->result_size = data->operand1_size;

	int i = 0;
	while (data->result_size >= data->operand2_size) // check if result size is greater than or equal to operand2 size
	{
		data->result_size = 0;
		subtraction(head1, tail1, head2, tail2, &temp_head, &temp_tail, data); // perform subtraction
		data->operand1_size = data->result_size;							   // update operand1 size

		delete_list(head1, tail1); // delete old operand1
		*head1 = temp_head;		   // update operand1
		*tail1 = temp_tail;

		temp_head = NULL; // reset temp_head & temp_tail
		temp_tail = NULL;
		temp = *head1;
		temp1 = *head2;

		quotient++;
		i++;

		if (data->operand2_size == data->result_size && temp->data < temp1->data) // if first operand is smaller and temp is NULL
		{
			break;
		}
		if (data->result_size == data->operand2_size) // if result size is equal to operand2 size
		{
			if (temp->next == NULL) // if last node of first operand is reached
			{
				if (temp->data == temp1->data) // if last digits are equal
				{
					quotient++;
					break;
				}
			}
			else
			{
				if (temp->data == temp1->data && (temp->next)->data < (temp1->next)->data) // if both digits are equal and first operand's next digit is smaller
					break;
			}
		}
	}

	while (quotient)
	{
		int num = quotient % 10;
		quotient /= 10;
		insert_first(headR, tailR, num);
	}

	if (val == 1) // If one operand is negative
	{
		insert_first(headR, tailR, 45); // insert -ve sign
	}

	return SUCCESS;
}
