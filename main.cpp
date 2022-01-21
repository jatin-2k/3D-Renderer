#include "provided/code/tgaimage.h"
#include "provided/code/geometry.h"
#include "line.h"
#include "model.h"
#include "triangle.h"
#include "variables.h"
#include <curses.h>
#include <iostream>

//Variables
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor black = TGAColor(  0,   0,   0,   0);
const TGAColor red   = TGAColor(255,   0,   0, 255);
Model *model = NULL;
const int width  = IMG_WIDTH;
const int height = IMG_HEIGHT;

//Functions
void inputModel(int argc, char** argv);
void draw(TGAImage &image);
void render(TGAImage &image);

int main(int argc, char** argv) {
	initscr();
	cbreak();

	char c;
	TGAImage image(width, height, TGAImage::RGB);

	Vec2i pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)}; 
    triangle(pts, image, red); 
	render(image);
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

void draw(TGAImage &image){
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, image, white);
        }
    }
}

void render(TGAImage &image){
	image.flip_vertically();
	image.write_tga_file("output.tga");
}