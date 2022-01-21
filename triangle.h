#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "provided/code/geometry.h"
#include "provided/code/tgaimage.h"

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
Vec3f cross(const Vec3f &v1, const Vec3f &v2);
Vec3f barycentric(Vec2i *pts, Vec2i P);
void triangle(Vec2i *pts, TGAImage &image, TGAColor color);

#endif