#include <math.h>
#include <iostream>
#include "tgaimage.h"

int diagonalDis(int x0, int y0, int x1, int y1){
	return sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
}

void line(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour){
	for(float cur=0; cur < 1; cur+=0.01){
		img.set(
			x0 + (x1-x0)*cur, 
			y0 + (y1-y0)*cur, 
			colour
		);
	}
}

