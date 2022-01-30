#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "provided/code/geometry.h"
#include "provided/code/tgaimage.h"
#include "model.h"

Vec3f barycentric(Vec2i *pts, Vec2i P);
Vec3f cross(const Vec3f &v1, const Vec3f &v2);
void OldSchooltriangle(Vec3f t0, Vec3f t1, Vec3f t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, TGAImage &image, Model* &model, float *zbuffer, float intensity);
void triangle(Vec2i *pts, TGAImage &image, TGAColor color);
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color);
void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, TGAColor color);
void triangle(Vec3f *pts, Vec3f *wpts, Vec2f *texture_pts, float *zbuffer, TGAImage &image, TGAImage &texture, float &intensity);

#endif