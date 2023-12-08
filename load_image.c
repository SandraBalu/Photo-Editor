#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_image.h"

void read_text2(char *filename, int ***black_and_white, int *height, int *width, int *scale)
{
	//open file to read
	FILE *file_photo;
	file_photo = fopen(filename, "rb");
	char format[3];
	//read photo format
	fscanf(file_photo, "%s", format);
	format[2] = '\0';
	char line[20];
	//read newline after P
	fgets(line, 20, file_photo);
	//read line with dimensions
	fgets(line, 20, file_photo);
	char *p;
	//search for the second value from the line
	p = strchr(line, ' ');
	//save the second value as the picture height
	*height = atoi(p + 1);
	//delete the second value from the line
	p[0] = '\0';
	//save the remaining value as the picture width
	*width = atoi(line);
	//read the new line on which the image scale is located
	fgets(line, 20, file_photo);
	*scale = atoi(line);
	//allocate memory for the 2-dimensional array with pixels
	(*black_and_white) = (int **)malloc(*height * sizeof(int *));
	for (int i = 0; i < *height; i++)
		(*black_and_white)[i] = (int *)malloc(*width * sizeof(int));

	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++) {
			int aux;
			//read pixel value
			fscanf(file_photo, "%d", &aux);
			//add the value in the matrix
			//printf("%c", aux);
			(*black_and_white)[i][j] = aux;
		}
	//close file opend in the function
	fclose(file_photo);
}

void read_text3(char *filename, int ****color, int *height, int *width, int *scale)
{
	//open file to read
	FILE *file_photo;
	file_photo = fopen(filename, "rb");
	char format[3];
	//read photo format
	fscanf(file_photo, "%s", format);
	format[2] = '\0';
	char line[20];
	//read newline after P
	fgets(line, 20, file_photo);
	//read line with dimensions
	fgets(line, 20, file_photo);
	char *p;
	//search for the second value from the line
	p = strchr(line, ' ');
	//save the second value as the picture height
	*height = atoi(p + 1);
	//delete the second value from the line
	p[0] = '\0';
	//save the remaining value as the picture width
	*width = atoi(line);
	//read the new line on which the image scale is located
	fgets(line, 20, file_photo);
	*scale = atoi(line);
	/*allocate memory for an array of matrices in order to
    create 3 matrices with pixels for each elementar color*/
	(*color) = (int ***)malloc(3 * sizeof(int **));
	for (int k = 0; k < 3; k++) {
		(*color)[k] = (int **)malloc(*height * sizeof(int *));
		for (int i = 0; i < *height; i++)
			(*color)[k][i] = (int *)malloc(*width * sizeof(int));
	}
	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++)
			for (int k = 0; k < 3; k++) {
				int aux;
				//read pixel value
				fscanf(file_photo, "%d", &aux);
				//add the value in the matrix
				//printf("%c", aux);
				(*color)[k][i][j] = aux;
			}
	fclose(file_photo);
}

void read_binary5(char *filename, int ***black_and_white, int *height, int *width, int *scale)
{
	//open file to read
	FILE *file_photo;
	file_photo = fopen(filename, "rb");
	char format[3];
	//read photo format
	fread(format, sizeof(char), 2, file_photo);
	format[2] = '\0';
	char line[20];
	//read newline after P
	fgets(line, 20, file_photo);
	//read line with dimensions
	fgets(line, 20, file_photo);
	char *p;
	//search for the second value from the line
	p = strchr(line, ' ');
	//save the second value as the picture height
	*height = atoi(p + 1);
	//delete the second value from the line
	p[0] = '\0';
	//save the remaining value as the picture width
	*width = atoi(line);
	//read the new line on which the image scale is located
	fgets(line, 20, file_photo);
	*scale = atoi(line);
	//allocate memory for the 2-dimensional array with pixels
	(*black_and_white) = (int **)malloc(*height * sizeof(int *));
	for (int i = 0; i < *height; i++)
		(*black_and_white)[i] = (int *)malloc(*width * sizeof(int));
	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++) {
			unsigned char aux;
			//read pixel value
			fread(&aux, sizeof(unsigned char), 1, file_photo);
			//add the value in the matrix
			(*black_and_white)[i][j] = aux;
		}
	fclose(file_photo);
}

void read_binary6(char *filename, int ****color, int *height, int *width, int *scale)
{
	FILE *file_photo;
	file_photo = fopen(filename, "rb");
	char format[3];
	//read photo format
	fread(format, sizeof(char), 2, file_photo);
	format[2] = '\0';
	char line[20];
	//read newline after P
	fgets(line, 20, file_photo);
	//read line with dimensions
	fgets(line, 20, file_photo);
	char *p;
	//search for the second value from the line
	p = strchr(line, ' ');
	//save the second value as the picture height
	*height = atoi(p + 1);
	//delete the second value from the line
	p[0] = '\0';
	//save the remaining value as the picture width
	*width = atoi(line);
	//read the new line on which the image scale is located
	fgets(line, 20, file_photo);
	*scale = atoi(line);
	/*allocate memory for an array of matrices in order to
    create 3 matrices with pixels for each elementar color*/
	(*color) = (int ***)malloc(3 * sizeof(int **));
	for (int k = 0; k < 3; k++) {
		(*color)[k] = (int **)malloc(*height * sizeof(int *));
		for (int i = 0; i < *height; i++)
			(*color)[k][i] = (int *)malloc(*width * sizeof(int));
	}
	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++)
			for (int k = 0; k < 3; k++) {
				unsigned char aux;
				//read pixel value
				fread(&aux, sizeof(unsigned char), 1, file_photo);
				//add the value in the matrix
				(*color)[k][i][j] = aux;
			}

	fclose(file_photo);
}