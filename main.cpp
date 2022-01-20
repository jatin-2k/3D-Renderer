#include "provided/code/tgaimage.h"
#include "line.h"
#include <curses.h>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor black = TGAColor(  0,   0,   0,   0);
const TGAColor red   = TGAColor(255,   0,   0, 255);

int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
	initscr();
	cbreak();

	char c;
	int x0 = 40, y0 = 20, x1 = 80, y1 = 80;
	supercoverLine(x0,y0,x1,y1,image,white);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	while(1){
		c = getch();
		system("clear");
		if(c=='q') break;
		image.flip_vertically();
		supercoverLine(x0,y0,x1,y1,image,black);
		switch (c)
		{
		case 'w': y0+=20; break;
		case 's': y0-=20; break;
		case 'a': x0-=20; break;
		case 'd': x0+=20; break;
		case 'i': y1+=20; break;
		case 'k': y1-=20; break;
		case 'j': x1-=20; break;
		case 'l': x1+=20; break;
		default:
			break;
		}
		std::cout<<"drawn:"<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<std::endl;
		supercoverLine(x0,y0,x1,y1,image,white);
		image.flip_vertically();
		image.write_tga_file("output.tga");
	}

	//image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	

	endwin();
	return 0;
}