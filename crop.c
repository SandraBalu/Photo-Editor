#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crop.h"
#include "utils.h"

void CROP_BA(int ***mat, int *x1, int *x2, int *y1, int *y2, int *height, int *width)
{
	int dim1 = *x2 - *x1, dim2 = *y2 - *y1;
	int **aux_mat = alloc_mat(dim2, dim1);
	int k = 0, p = 0, i, j;
	for (i = *y1; i < *y2; i++) {
		p = 0;
		for (j = *x1; j < *x2; j++) {
			aux_mat[k][p] = (*mat)[i][j];
			p++;
		}
		k++;
	}
	//sanve new dimmensions
	*height = dim2;
	*width = dim1;
	free_b_and_w(mat, *height);
	(*mat) = aux_mat;
	*x1 = 0;
	*x2 = *width;
	*y1 = 0;
	*y2 = *height;
}

void CROP_C(int ****mat, int *x1, int *x2, int *y1, int *y2, int *height, int *width)
{
	int dim1 = *x2 - *x1, dim2 = *y2 - *y1;
	int ***aux_mat = (int ***)malloc(3 * sizeof(int **));
	for (int i = 0; i < 3; i++)
		aux_mat[i] = alloc_mat(dim2, dim1);
	// for(int p = 0; p < 3; p++){
	//     int k = 0, q = 0, i, j;
	//     for (i = *y1; i < *y2; i++){
	//         q = 0;
	// 	    for (j = *x1; j < *x2; j++){
	//             aux_mat[k][q] = (*mat)[p][i][j];
	//             q++;
	//         }
	//         k++;
	//     }
	//     (*mat)[k] = aux_mat;
	// }
	//printf("%d %d %d\n", (*mat)[0][0][0], (*mat)[1][0][0], (*mat)[2][0][0]);
	for (int p = 0; p < 3; p++) {
		for (int i = 0; i < dim2; i++) {
			for (int j = 0; j < dim1; j++) {
				aux_mat[p][i][j] = (*mat)[p][*y1 + i][*x1 + j];
			}
		}
		for (int i = 0; i < *height; ++i)
			free((*mat)[p][i]);
		free((*mat)[p]);
		(*mat)[p] = aux_mat[p];
	}

	//save new dimmensions
	*height = dim2;
	*width = dim1;
	*x1 = 0;
	*x2 = *width;
	*y1 = 0;
	*y2 = *height;
}

void apply_CROP(int ****color, int ***black_and_white, int *x1,
		int *x2, int *y1, int *y2, int *heigt, int *width, char format)
{
	if (format == '2' || format == '5') {
		//corp black and white picture
		CROP_BA(black_and_white, x1, x2, y1, y2, heigt, width);
	} else {
		CROP_C(color, x1, x2, y1, y2, heigt, width);
	}
	printf("Image cropped\n");
}