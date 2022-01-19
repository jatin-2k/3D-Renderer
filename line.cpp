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

void optLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour){
	float cur = 0;
	int points = diagonalDis(x0,y0,x1,y1);
	for(float i=0; i<points; i+=1, cur = i/points){
		img.set(
			x0 + (x1-x0)*cur, 
			y0 + (y1-y0)*cur, 
			colour
		);
	}
}

void walkLine(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour){
	int dx = x1-x0, dy = y1-y0; //diplacement
	int nx = abs(dx), ny = abs(dy); //number of points
	int sign_x = (dx>0)?1:-1 , sign_y = (dy>0)?1:-1;
	int px = x0, py = y0;
	for(int ix=0, iy=0; ix<nx || iy<ny; ){
		//if((0.5 + ix)/nx < (0.5 + iy)/ny)
		if((1 + 2*ix) * ny < (1 + 2*iy) * nx){
			px = px + sign_x;
			ix++;
		}
		else{
			py = py + sign_y;
			iy++;
		}
		img.set(px,py,colour);
	}
}