#pragma once

//function used to crop black and white picture
void CROP_BA(int ***mat, int *x1, int *x2, int *y1, int *y2, int *height, int *width);

//function used to crop colored picture
void CROP_C(int ****mat, int *x1, int *x2, int *y1, int *y2, int *height, int *width);

//functio used to crop picture depending on format
void apply_CROP(int ****color, int ***black_and_white, int *x1,
		int *x2, int *y1, int *y2, int *heigt, int *width, char format);