#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotate.h"
#include "utils.h"

void rotate90LEFT(int ***mat, int x1, int x2, int y1, int y2)
{
	int dim = x2 - x1, k = 0, p = 0, i, j;
	//create new matrix in oreder to build the transposed
	int **mat_trans = alloc_mat(dim, dim);
	for (i = y1; i < y2; i++) {
		p = 0;
		for (j = x1; j < x2; j++) {
			mat_trans[k][p] = (*mat)[j][i];
			p++;
		}
		k++;
	}
	k = 0;
	p = 0;
	for (i = y1; i < y2; i++) {
		p = 0;
		for (j = x1; j < x2; j++) {
			(*mat)[i][j] = mat_trans[k][p];
			p++;
		}
		k++;
	}
	free_b_and_w(&mat_trans, dim);
}

void rotate90all(int ***mat, int *x2, int *y2, int *width, int *height)
{
	int k = 0, p = 0, i, j;
	//create new matrix in oreder to build the transposed
	int **mat_trans = alloc_mat(*width, *height);
	for (i = 0; i < *height; i++) {
		p = 0;
		for (j = 0; j < *width; j++) {
			mat_trans[k][p] = (*mat)[j][i];
			p++;
		}
		k++;
	}
	free_b_and_w(mat, *height);
	(*mat) = alloc_mat(*width, *height);

	k = 0;
	p = 0;
	for (i = 0; i < *width; i++) {
		p = 0;
		for (j = 0; j < *height; j++) {
			(*mat)[i][j] = mat_trans[k][p];
			p++;
		}
		k++;
	}
	free_b_and_w(&mat_trans, *width);
	int aux;
	*x2 = *height;
	*y2 = *width;
	aux = *height;
	*height = *width;
	*width = aux;
}

int ROTATE(int ***mat, int *x1, int *y1, int *x2, int *y2, char *command, int *angle, int *height, int *width)
{

	char nr[10];
	strcpy(nr, command + 7);
	if (nr[0] == '-') {
		*angle = atoi(nr + 1);
		*angle *= (-1);
	} else {
		*angle = atoi(nr);
	}

	//verify if the rotation agle is supported
	if (*angle > 360 || *angle < -360) {
		printf("Unsupported rotation angle\n");
		return 0;
	}
	if (abs(*angle) % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return 0;
	}
	if (x2 - x1 != y2 - y1) {
		printf("The selection must be square\n");
		return 0;
	}
	if (*x1 == 0 && *x2 == *width && *y1 == 0 && *y2 == *height) {
		//rotete once to the left
		if (*angle == -90 || *angle == 270)
			rotate90all(mat, x2, y2, height, width);

		//rotate twice to the left
		if (*angle == -180 || *angle == 180) {
			rotate90all(mat, x2, y2, height, width);
			rotate90all(mat, x2, y2, height, width);
		}
		//rotate 3 times to the left
		if (*angle == -270 || *angle == 90) {
			rotate90all(mat, x2, y2, height, width);
			rotate90all(mat, x2, y2, height, width);
			rotate90all(mat, x2, y2, height, width);
		}
		return 1;

	} else {
		//rotete once to the left
		if (*angle == -90 || *angle == 270)
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);

		//rotate twice to the left
		if (*angle == -180 || *angle == 180) {
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);
			// if(*x2 == *width && *x1 == 0 && *y1 == 0 && *y2 == *height){
			//     swap(x2, y2);
			//     swap(height, width);
			// }
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);
		}
		//rotate 3 times to the left
		if (*angle == -270 || *angle == 90) {
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);
			;
			rotate90LEFT(mat, *x1, *x2, *y1, *y2);
		}

		return 1;
	}
}
