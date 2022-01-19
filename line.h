#ifndef _LINE_H
#define _LINE_H

#include "provided/code/tgaimage.h"

//Function Declerations
int diagonalDis(int x0, int y0, int x1, int y1);
void unoptLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour);
void optLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour);
void walkLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour);
void supercoverLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour);

#endif