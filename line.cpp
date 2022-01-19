#include <math.h>
#include <iostream>
#include "provided/code/tgaimage.h"

int diagonalDis(int x0, int y0, int x1, int y1){
	return sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
}

void unoptLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour){
	for(float cur=0; cur < 1; cur+=0.01){
		img.set(
			x0 + (x1-x0)*cur, 
			y0 + (y1-y0)*cur, 
			colour
		);
	}
}

void optLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour, int points){
	float cur = 0;
	for(float i=0; i<points; i+=1, cur = i/points){
		img.set(
			x0 + (x1-x0)*cur, 
			y0 + (y1-y0)*cur, 
			colour
		);
	}
}