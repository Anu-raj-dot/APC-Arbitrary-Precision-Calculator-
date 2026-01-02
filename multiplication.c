/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
            : tail1: Pointer to the last node of the first double linked list.
            : head2: Pointer to the first node of the second double linked list.
            : tail2: Pointer to the last node of the second double linked list.
            : headR: Pointer to the first node of the resultant double linked list.
            : tailR: Pointer to the last node of the resultant double linked list.
            : data: Pointer to the Data structure containing operand sizes and result size.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/

#include "apc.h"
#include "common.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Data *data)
{
    int val = data->operand1_sign + data->operand2_sign;
    data->operand1_sign = 0; // Reset operand signs for multiplication
    data->operand2_sign = 0;

    if ((data->operand1_size == 1 && (*head1)->data == 0) || (data->operand2_size == 1 && (*head2)->data == 0)) // Zero check
    {
        insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *temp = *tail2;
    Dlist *temp_head = NULL;
    Dlist *temp_tail = NULL;
    Dlist *temp1_head = NULL;
    Dlist *temp1_tail = NULL;

    int i = 0;
    int carry, flag = 1;

    while (i < data->operand2_size) // Loop through each digit of operand2
    {
        Dlist *temp1 = *tail1;
        carry = 0;

        for (int j = 0; j < i; j++) // Zero padding for partial product
        {
            insert_first(&temp1_head, &temp1_tail, 0);
        }

        while (temp1) // Multiply current digit of operand2 with all digits of operand1
        {
            int num = temp1->data * temp->data + carry;
            carry = num / 10; // Always set carry
            num = num % 10;

            if (flag)
                insert_first(&temp_head, &temp_tail, num);
            else
                insert_first(&temp1_head, &temp1_tail, num);

            temp1 = temp1->prev;

            if (temp1 == NULL && carry != 0) // Remaining carry after last digit
            {
                if (flag) // First iteration case
                    insert_first(&temp_head, &temp_tail, carry);
                else
                    insert_first(&temp1_head, &temp1_tail, carry);
            }
        }

        if (i == 0 && data->operand2_size == 1) // First iteration special case
        {
            *headR = temp_head;
            *tailR = temp_tail;
        }
        else if (i >= 1)
        {
            addition(&temp_head, &temp_tail, &temp1_head, &temp1_tail, headR, tailR, data); // add addition of partial products

            delete_list(&temp_head, &temp_tail); // Clean up old temp lists
            delete_list(&temp1_head, &temp1_tail);

            temp_head = *headR;
            temp_tail = *tailR;
            *headR = NULL;
            *tailR = NULL;
        }

        flag = 0;
        temp = temp->prev;

        if (temp1_head != NULL || temp1_tail != NULL) // Delete any partial product list before next loop
        {
            delete_list(&temp1_head, &temp1_tail);
        }

        if (temp == NULL) // Final result assignment after loop ends
        {
            *headR = temp_head;
            *tailR = temp_tail;
        }

        i++;
    }

    if (val == 1) // if one operand is negative
    {
        insert_first(headR, tailR, 45);
    }

    return SUCCESS;
}