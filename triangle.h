#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "provided/code/geometry.h"
#include "provided/code/tgaimage.h"

Vec3f barycentric(Vec2i *pts, Vec2i P);
Vec3f cross(const Vec3f &v1, const Vec3f &v2);
void triangle(Vec2i *pts, TGAImage &image, TGAColor color);
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, TGAColor color);

#endif