#pragma once

//read black and white photo from text file
void read_text2(char *filename, int ***black_and_white, int *height, int *width, int *scale);

//read colored picture from text file
void read_text3(char *filename, int ****color, int *height, int *width, int *scale);

//read black and white photo from binary file
void read_binary5(char *filename, int ***black_and_white, int *height, int *width, int *scale);

//read colored picture from binary file
void read_binary6(char *filename, int ****color, int *height, int *width, int *scale);