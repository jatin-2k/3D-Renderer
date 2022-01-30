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
Vec3f world2screen(Vec3f v);
void drawWireFrameOn(TGAImage &image);
void drawFlatShadingRenderOn(TGAImage &image);
void drawShadedRenderOn(TGAImage &image);
void drawTextureRenderOn(TGAImage &image, TGAImage &texture);
void render(TGAImage &image);

int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);

	inputModel(argc,argv);
    drawFlatShadingRenderOn(image);
	render(image);
    delete model;
	return 0;
}

#pragma region Function_Definations
void inputModel(int argc, char** argv){
	if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("./provided/obj/african_head.obj");
    }
}

void drawFlatShadingRenderOn(TGAImage &image){
    float *zbuffer = new float[width*height];
    for (int i=width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());
	for (int i=0; i<model->nfaces(); i++) { 
		std::vector<int> face = model->face(i); 
        Vec3f screen_coords[3]; 
        Vec3f world_coords[3]; 
        Vec2i texture_coords[3];
        for (int j=0; j<3; j++) { 
            Vec3f v = model->vert(face[j]); 
            Vec2f t = model->uv(i,j);
            screen_coords[j] = world2screen(v);
            world_coords[j]  = v; 
            texture_coords[j] = t;
        } 
        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]); 
        Vec3f light_dir(0,0,-1);
        n.normalize(); 
        float intensity = n*light_dir; 
        if(intensity > 0)
		triangle(screen_coords, texture_coords, zbuffer, image, model, intensity); 
	}
}

Vec3f world2screen(Vec3f v) {
    return Vec3f(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}

void render(TGAImage &image){
	image.flip_vertically();
	image.write_tga_file("output.tga");
}
#pragma endregion