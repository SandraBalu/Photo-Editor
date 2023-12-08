#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crop.h"
#include "histogram.h"
#include "load_image.h"
#include "rotate.h"
#include "save.h"
#include "select.h"
#include "utils.h"

int main()
{
	char operation[100];
	char photo_format[3];
	int height, width, scale, x1, x2, y1, y2, ok = 0, ms = 0;
	fgets(operation, 100, stdin);
	operation[strlen(operation) - 1] = '\0';
	int ***color = NULL;
	int **black_and_white = NULL;
	char exit[4] = "EXIT";
	// as long as the operation is not exit, analyze the requested operation
	while (strncmp(operation, exit, 3) != 0) {
		if (strncmp(operation, "LOAD", 4) == 0) {
			char filename[60];
			ok = 1;
			strcpy(filename, operation + 5);
			FILE *file_photo;
			file_photo = fopen(filename, "rt");
			if (file_photo == NULL) {
				printf("Failed to load %s\n", filename);
				ok = 0;
				ms = 1;
			} else {

				fscanf(file_photo, "%s", photo_format);
				fclose(file_photo);

				// read black and white photo
				if (photo_format[1] == '2')
					read_text2(filename, &black_and_white,
						   &height, &width, &scale);

				// read color photo
				if (photo_format[1] == '3')
					read_text3(filename, &color, &height,
						   &width, &scale);

				// read black and white photo
				if (photo_format[1] == '5')
					read_binary5(filename, &black_and_white,
						     &height, &width, &scale);

				// read color photo
				if (photo_format[1] == '6')
					read_binary6(filename, &color, &height,
						     &width, &scale);

				verify_loaded(photo_format, filename,
					      black_and_white, color);
				x1 = 0;
				x2 = width;
				y1 = 0;
				y2 = height;
			}
		}

		if (ok == 0 && ms == 0)
			printf("No image loaded\n");
		if (ok == 1)
			verif_command(operation);
		if (strncmp(operation, "SELECT", 6) == 0 && ok == 1)
			SELECT(&x1, &y1, &x2, &y2, height, width, operation);

		if (strncmp(operation, "CROP", 4) == 0 && ok == 1)
			apply_CROP(&color, &black_and_white, &x1, &x2, &y1, &y2,
				   &height, &width, photo_format[1]);

		if (strncmp(operation, "ROTATE", 6) == 0 && ok == 1) {
			int angle;
			if (photo_format[1] == '2' || photo_format[1] == '5') {
				if (ROTATE(&black_and_white, &x1, &y1, &x2, &y2,
					   operation, &angle, &height,
					   &width) == 1)
					printf("Rotated %d\n", angle);

			} else {
				int v;
				for (int i = 0; i < 3; i++)
					v = ROTATE(&color[i], &x1, &y1, &x2,
						   &y2, operation, &angle,
						   &height, &width);
				if (v == 1)
					printf("Rotated %d\n", angle);
			}
		}
		if (strncmp(operation, "HISTOGRAM", 9) == 0 && ok == 1)
			HISTOGRAM(photo_format[1], black_and_white, height,
				  width, operation);

		if (strncmp(operation, "SAVE", 4) == 0 && ok == 1)
			save(black_and_white, color, operation, photo_format[1],
			     height, width);

		fgets(operation, 100, stdin);
		operation[strlen(operation) - 1] = '\0';
		ms = 0;
	}
	if (ok == 0 && ms == 0)
		printf("No image loaded\n");

	// delete_picture(&black_and_white, &color, &height, &width);
	return 0;
}
