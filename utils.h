#pragma once

void verif_command(char *command);

//verify ifthe photo has been uploaded in the memory
void verify_loaded(char *photo_format, char *filename, int **black_and_white, int ***color);

//function used to free matrix for black and white pictures
void free_b_and_w(int ***mat, int dim);

//function used to free matrix for black and white pictures
void free_color(int ****mat, int dim);

//function used to delete existing matrix when uploaded aa new one
void delete_picture(int ***black_and_white, int ****color, int *height, int *width);

//function used to verify if the coordinats from the selections are valid
int verif_SELECT(int a1, int a2, int b1, int b2, int height, int width);

//interchange 2 values
void swap(int *x, int *y);

//function used to alloc memory for 2D-matrix
int **alloc_mat(int n, int m);

//funtion used to initialize array with zeros
void initialize(double **mat, int dim);