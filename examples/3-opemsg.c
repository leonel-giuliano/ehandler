#define USE_OPEMSG


#include <stdio.h>

#include "ehandler.h"


int print_input(void) {
	int var;

	scanf("%d", &var);
	if(var < 0) {
		set_opemsg("Input should be greater than 0");
		return -1;
	}

	if(var > 10) {
		set_opemsg("Input should be less than 10");
		return -1;
	}

	printf("Input: %d\n", var);
	return 0;
}


int main(void) {
	if(print_input() == -1)
		EHANDLER("Problem printing", -1);

	puts("No errors\n");
	return 0;
}
