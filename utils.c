#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void verif_command(char *command)
{
	if (strcmp(command, "APPLY") == 0)
		printf("Invalid command\n");
}

void verify_loaded(char *photo_format, char *filename, int **black_and_white, int ***color)
{
	if (photo_format[1] == '2') {
		if (**black_and_white)
			printf("Loaded %s\n", filename);
		else
			printf("Failed to load %s\n", filename);
	}

	if (photo_format[1] == '5') {
		if (**black_and_white)
			printf("Loaded %s\n", filename);
		else
			printf("Failed to load %s\n", filename);
	}

	if (photo_format[1] == '3') {
		if (***color)
			printf("Loaded %s\n", filename);
		else
			printf("Failed to load %s\n", filename);
	}

	if (photo_format[1] == '6') {
		if (***color)
			printf("Loaded %s\n", filename);
		else
			printf("Failed to load %s\n", filename);
	}
}

void free_b_and_w(int ***mat, int dim)
{
	for (int i = 0; i < dim; i++)
		free((*mat)[i]);
	free(*mat);
}

void free_color(int ****mat, int dim)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < dim; j++)
			free((*mat)[i][j]);
	for (int i = 0; i < 3; i++)
		free((*mat)[i]);
	free(*mat);
}

void delete_picture(int ***black_and_white, int ****color, int *height, int *width)
{
	if (black_and_white)
		free_b_and_w(black_and_white, *height);
	if (color)
		free_color(color, *height);
	*height = 0;
	*width = 0;
}

int verif_SELECT(int a1, int a2, int b1, int b2, int height, int width)
{
	if (a1 < 0 || b1 < 0) {
		printf("Invalid set of coordinates\n");
		return -1;
	}
	if (a2 > width || b2 > height) {
		printf("Invalid set of coordinates\n");
		return -1;
	}

	// if( a1 == b1 || a2 == b2 ){
	//     printf("Invalid set of coordinates\n");
	//     return -1;
	// }
	return 1;
}

void swap(int *x, int *y)
{
	//swap intre 2 int-uri
	int aux = *x;
	*x = *y;
	*y = aux;
}

int **alloc_mat(int n, int m)
{
	int **matrix = (int **)malloc(n * sizeof(int *));
	//check dynamic memory allocation
	if (!matrix)
		return NULL;
	for (int i = 0; i < n; i++) {
		matrix[i] = (int *)malloc(m * sizeof(int));
		if (!matrix[i]) {
			return NULL;
			free(matrix[i]);
		}
	}
	return matrix;
}

void initialize(double **mat, int dim)
{
	for (int i = 0; i < dim; i++)
		(*mat)[i] = 0;
}