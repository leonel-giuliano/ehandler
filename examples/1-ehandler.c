#include <stdio.h>


#include "ehandler.h"


int main(void) {
	int var;

	scanf("%d", &var);
	if(var < 0) EHANDLER("Input should be greater than 0", -1);

	printf("Your input was: %d\n", var);
	return 0;
}
