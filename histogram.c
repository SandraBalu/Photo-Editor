#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "histogram.h"
#include "utils.h"

void det_fr(double **fr, int **mat, int height, int width)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			(*fr)[mat[i][j]]++;
}

void HISTOGRAM(char format, int **mat, int height, int width, char *command)
{

	if (format == '3' || format == '6') {
		printf("Black and white image needed\n");
		return;
	}
	int x, y;
	char val[20];
	strcpy(val, command + 10);
	char *p = strtok(val, " ");
	x = atoi(p);
	p = strtok(NULL, " ");
	y = atoi(p);
	double **copy;
	copy = (double **)malloc(height * sizeof(double));
	for (int i = 0; i < height; i++)
		copy[i] = (double *)malloc(width * sizeof(double));

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			copy[i][j] = (double)mat[i][j];

	double *frequency;
	frequency = (double *)malloc(256 * sizeof(double));
	initialize(&frequency, 257);
	det_fr(&frequency, mat, height, width);
	double max = -1;
	int interval = 256 / y;
	int aux = 0;
	while (aux < interval) {
		double sum = 0;
		for (int i = aux * y; i < (aux + 1) * y; i++) {
			sum += frequency[i];
		}
		if (sum > max)
			max = sum;
		aux++;
	}
	aux = 0;
	while (aux < interval) {
		double sum = 0;
		for (int i = aux * y; i < (aux + 1) * y; i++) {
			sum += frequency[i];
		}
		double stars = 0;
		stars = floor(sum / max * x);
		printf("%d\t|\t", (int)stars);
		for (double k = 0; k < stars; k++)
			printf("*");
		printf("\n");
		aux++;
	}

	for (int i = 0; i < height; i++)
		free(copy[i]);
	free(copy);
	free(frequency);
}