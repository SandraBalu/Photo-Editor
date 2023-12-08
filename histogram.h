#pragma once

//function used to determinate the frequency of each pixel value
void det_fr(double **fr, int **mat, int height, int width);

//function used to verify if the hidtogram can be generated and also generates it
void HISTOGRAM(char format, int **mat, int height, int width, char *command);