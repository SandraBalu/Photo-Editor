#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "select.h"
#include "utils.h"

void SELECT(int *x1, int *y1, int *x2, int *y2, int height, int width, char *command)
{
	char numbers[20];
	int i = 0, ok, a1, b1, a2, b2;
	if (strlen(command) != 10) {
		//sacve the number values from the command
		strcpy(numbers, command + 6);
		char *p;
		p = strtok(numbers, " ");
		while (p != NULL) {
			//save the values in the arrey
			unsigned int t = atoi(p);
			int z = (int)t;
			if (i == 0)
				a1 = z;
			if (i == 1)
				b1 = z;
			if (i == 2)
				a2 = z;
			if (i == 3)
				b2 = z;
			i++;
			p = strtok(NULL, " ");
		}
		//verify if the coordinates are valid
		ok = verif_SELECT(a1, a2, b1, b2, height, width);
		if (ok > 0) {
			//if the coordinats are valid, check their order
			if (a1 > a2)
				swap(&a1, &a2);
			if (b1 > b2)
				swap(&b1, &b2);
			//save the selection
			*x1 = a1;
			*y1 = b1;
			*x2 = a2;
			*y2 = b2;
			printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
		}
	} else {
		printf("Selected ALL\n");
	}
}