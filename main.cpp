#include "provided/code/tgaimage.h"
#include "provided/code/geometry.h"
#include "line.h"
#include "model.h"
#include <curses.h>
#include <iostream>

//Variables
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor black = TGAColor(  0,   0,   0,   0);
const TGAColor red   = TGAColor(255,   0,   0, 255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

//Functions
void inputModel(int argc, char** argv);
int main(int argc, char** argv) {
	initscr();
	cbreak();

	char c;
	TGAImage image(width, height, TGAImage::RGB);

	inputModel(argc, argv);
	while(1){
		c = getch();
		system("clear");
		if(c=='q') break;
		//will write rotation code here
	}


	endwin();
	return 0;
}

void inputModel(int argc, char** argv){
	if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("./provided/obj/african_head.obj");
    }
}
