#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_text(int **mat, int ***mat_c, int height, int width, char photo_format, char *filename)
{
	FILE *where_to_save = fopen(filename, "w");
	if (photo_format == '5')
		photo_format = '2';
	if (photo_format == '6')
		photo_format = '3';
	fprintf(where_to_save, "P%c\n", photo_format);
	fprintf(where_to_save, "%d %d\n", width, height);
	fprintf(where_to_save, "%d\n", 255);
	if (photo_format == '2' || photo_format == '5') {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				unsigned char aux = mat[i][j];
				fprintf(where_to_save, "%d ", aux);
			}
			fprintf(where_to_save, "\n");
		}
	} else {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				for (int k = 0; k < 3; k++) {
					unsigned char aux = mat_c[k][i][j];
					fprintf(where_to_save, "%d ", aux);
				}
		}
	}
	fclose(where_to_save);
}

void write_binary(int **mat, int ***mat_c, int height, int width, char photo_format, char *filename)
{

	FILE *where_to_write = fopen(filename, "w");
	if (photo_format == '2')
		photo_format = '5';
	if (photo_format == '3')
		photo_format = '6';
	fprintf(where_to_write, "P%c\n", photo_format);
	fprintf(where_to_write, "%d %d\n", width, height);
	fprintf(where_to_write, "%d\n", 255);
	// fclose(where_to_write);

	// where_to_write = fopen(filename, "wb");
	if (photo_format == '5' || photo_format == '2') {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				unsigned char aux = mat[i][j];
				fwrite(&aux, sizeof(unsigned char), 1, where_to_write);
			}
		}
	} else {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				for (int k = 0; k < 3; k++) {
					unsigned char aux = mat_c[k][i][j];
					fwrite(&aux, sizeof(unsigned char), 1, where_to_write);
				}
		}
	}
	fclose(where_to_write);
}

void save(int **b_w, int ***color, char *command, char phhot_format, int height, int width)
{
	char filename[60];
	strcpy(filename, command + 5);
	if (strchr(filename, ' ') != NULL) {
		char *p = strchr(filename, ' ');
		*p = '\0';
		write_text(b_w, color, height, width, phhot_format, filename);
	} else {
		write_binary(b_w, color, height, width, phhot_format, filename);
	}
	printf("Saved %s\n", filename);
}