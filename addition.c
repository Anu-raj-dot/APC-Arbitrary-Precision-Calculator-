/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
			: tailR: Pointer to the last node of the resultant double linked list.
			: data : Pointer to the data structure containing the operands.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"
#include "common.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data)
{
	if (data->operand1_sign == 0 && data->operand2_sign == 1) // If second operand is negative, perform subtraction
	{
		subtraction(head1, tail1, head2, tail2, headR, tailR, data);
		return SUCCESS;
	}

	if (data->operand1_sign == 1 && data->operand2_sign == 0) // If second operand is negative, perform subtraction
	{
		int val = data->operand1_size;
		data->operand1_size = data->operand2_size;
		data->operand2_size = val;
		subtraction(head2, tail2, head1, tail1, headR, tailR, data);
		return SUCCESS;
	}

	int carry = 0, sum = 0;

	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	while (temp1 != NULL || temp2 != NULL || carry) // Run until all digits are processed
	{
		if (temp1 == NULL && temp2 != NULL) // if first list has ended
			sum = 0 + temp2->data + carry;
		else if (temp2 == NULL && temp1 != NULL) // if second list has ended
			sum = temp1->data + 0 + carry;
		else if (temp1 == NULL && temp2 == NULL) // if both lists have ended and carry is present
			sum = 0 + 0 + carry;
		else
			sum = temp1->data + temp2->data + carry;

		if (sum > 9) // if sum is greater than 9
		{
			carry = 1;
			sum = sum - 10;
		}
		else
			carry = 0;

		insert_first(headR, tailR, sum); // insert the sum at the beginning of the resultant list

		temp1 = (temp1 != NULL ? temp1->prev : NULL); // move to the previous node in the first list
		temp2 = (temp2 != NULL ? temp2->prev : NULL); // move to the previous node in the second list
	}

	if (data->operand1_sign == 1 && data->operand2_sign == 1) // If first and second operands are negative
	{
		insert_first(headR, tailR, 45); // insert -ve sign
	}
	return SUCCESS;
}