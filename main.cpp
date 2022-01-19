#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

//Function Declerations
void line(int x0, int y0, int x1, int y1, TGAImage &img, TGAColor colour);


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	line(0,0,100,100,image,red);

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
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