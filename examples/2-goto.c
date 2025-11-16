#include <stdio.h>
#include <stdlib.h>

#include "ehandler.h"


int main(void) {
	int e = 0;
	int input;
	int *pvar;

	scanf("%d", &input);
	if((pvar = (int *)malloc(input * sizeof(int))) == NULL)
		EHANDLER_GOTO("Problem allocating", -1, free_var);

	printf("Input '%d' created a var of size '%d'\n",
			input, input * sizeof(int));

	free_var:
		free(pvar);
		return e;
}
