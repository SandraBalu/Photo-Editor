#pragma once

//functio used to write in text file
void write_text(int **mat, int ***mat_c, int height, int width, char photo_format, char *filename);

//function used to write in binary file
void write_binary(int **mat, int height, int width, char photo_format, char *filename);

//function used to write
void save(int **b_w, int ***color, char *command, char phhot_format, int height, int width);