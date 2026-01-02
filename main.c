/**************************************************************************************************************************************************************
	   PROJECT : APC - Arbitrary Precision Calculator
 ***************************************************************************************************************************************************************/
#include "apc.h"
#include "common.h"

int main(int argc, char *argv[])
{
	/* Declare the pointers */
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	Data data;
	char option, operator;

	head1 = tail1 = head2 = tail2 = headR = tailR = NULL;
	data.operand1_sign = 0;
	data.operand2_sign = 0;

	if (validate_args(argc, argv, &operator) == FAILURE)
	{
		printf("INFO : ./a.out <operand1> <operator(+,-,x,/)> <operand2>\n");
		printf("INFO : For multiplication operation, use 'x' instead of '*'\n");
		return FAILURE;
	}

	switch (operator)
	{
	case '+':
	{
		/* call the function to perform the addition operation */
		if (operand_node(&head1, &tail1, &head2, &tail2, argv, &data) == FAILURE)
		{
			printf("ERROR : Failed to create double linked list for operands\n");
			return FAILURE;
		}
		if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR, &data) == FAILURE)
		{
			printf("ERROR : Addition failed\n");
			return FAILURE;
		}
		print_list(headR);
		delete_list(&head1, &tail1);
		delete_list(&head2, &tail2);
		delete_list(&headR, &tailR);
	}
	break;
	case '-':
	{
		/* call the function to perform the subtraction operation */
		if (operand_node(&head1, &tail1, &head2, &tail2, argv, &data) == FAILURE)
		{
			printf("ERROR : Failed to create double linked list for operands\n");
			return FAILURE;
		}
		if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, &data) == FAILURE)
		{
			printf("ERROR : Substraction failed\n");
			return FAILURE;
		}
		print_list(headR);
		delete_list(&head1, &tail1);
		delete_list(&head2, &tail2);
		delete_list(&headR, &tailR);
	}
	break;
	case 'x':
	{
		/* call the function to perform the multiplication operation */
		if (operand_node(&head1, &tail1, &head2, &tail2, argv, &data) == FAILURE)
		{
			printf("ERROR : Failed to create double linked list for operands\n");
			return FAILURE;
		}
		if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR, &data) == FAILURE)
		{
			printf("ERROR : Multiplication failed\n");
			return FAILURE;
		}
		print_list(headR);
		delete_list(&headR, &tailR);
	}
	break;
	case '/':
	{
		/* call the function to perform the division operation */
		if (operand_node(&head1, &tail1, &head2, &tail2, argv, &data) == FAILURE)
		{
			printf("ERROR : Failed to create double linked list for operands\n");
			return FAILURE;
		}
		int ret;
		if ((ret = division(&head1, &tail1, &head2, &tail2, &headR, &tailR, &data)) == FAILURE)
		{
			printf("ERROR : Division failed\n");
			return FAILURE;
		}
		else if (ret == ZERO_ERROR)
		{
			printf("ERROR : Division by zero\n");
			return FAILURE;
		}
		print_list(headR);
		delete_list(&head2, &tail2);
		delete_list(&headR, &tailR);
	}
	break;
	default:
	{
		printf("Invalid Input:-( Try again... )\n");
		printf("INFO : ./a.out <operand1> <operator(+,-,x,/)> <operand2>\n");
		printf("INFO : For multiplication operation, use 'x' instead of '*'\n");
	}
	}

	return 0;
}

/* Function for extracting the operator & validating the operands */
int validate_args(int argc, char *argv[], char *ch)
{
	if (argc != 4)
	{
		printf("ERROR : Argument count is less\n");
		return FAILURE;
	}

	char *ext[4] = {"+", "-", "x", "/"};
	int size = sizeof(ext) / sizeof(ext[0]);
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (strcmp(argv[2], ext[i]) == 0)
		{
			strcpy(ch, argv[2]);
		}
		else
		{
			count++;
			if (count == 4)
			{
				printf("ERROR : Invalid operator\n");
				return FAILURE;
			}
		}
	}

	int i = 0;
	while (argv[1][i])
	{
		if (argv[1][0] == '-' && i == 0)
		{
			i++;
		}
		else if (argv[1][i] >= '0' && argv[1][i] <= '9')
		{
			i++;
		}
		else
		{
			printf("ERROR : Operand only contain digits\n");
			return FAILURE;
		}
	}

	i = 0;
	while (argv[3][i])
	{
		if (argv[3][i] == '-' && i == 0)
		{
			i++;
		}
		else if (argv[3][i] >= '0' && argv[3][i] <= '9')
		{
			i++;
		}
		else
		{
			printf("ERROR : Operand only contain digits\n");
			return FAILURE;
		}
	}

	return SUCCESS;
}
