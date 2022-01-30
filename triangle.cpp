#include "triangle.h"

void OldSchooltriangle(Vec3f t0, Vec3f t1, Vec3f t2, Vec2i uv0, Vec2i uv1, Vec2i uv2, TGAImage &image, Model* &model, float *zbuffer, float intensity) {
    if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
    if (t0.y>t1.y) { std::swap(t0, t1); std::swap(uv0, uv1); }
    if (t0.y>t2.y) { std::swap(t0, t2); std::swap(uv0, uv2); }
    if (t1.y>t2.y) { std::swap(t1, t2); std::swap(uv1, uv2); }

    int total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
        Vec3i A   =               t0  + Vec3f(t2-t0  )*alpha;
        Vec3i B   = second_half ? t1  + Vec3f(t2-t1  )*beta : t0  + Vec3f(t1-t0  )*beta;
        Vec2i uvA =               uv0 +      (uv2-uv0)*alpha;
        Vec2i uvB = second_half ? uv1 +      (uv2-uv1)*beta : uv0 +      (uv1-uv0)*beta;
        if (A.x>B.x) { std::swap(A, B); std::swap(uvA, uvB); }
        for (int j=A.x; j<=B.x; j++) {
            float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
            Vec3i   P = Vec3f(A) + Vec3f(B-A)*phi;
            Vec2i uvP =     uvA +   (uvB-uvA)*phi;
            int idx = P.x+P.y*image.get_width();
            if (zbuffer[idx]<P.z) {
                zbuffer[idx] = P.z;
                TGAColor color = model->diffuse(uvP);
                image.set(P.x, P.y, TGAColor(color.bgra[2]*intensity, color.bgra[1]*intensity, color.bgra[0]*intensity));
            }
        }
    }
}

Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
    return Vec3f(v1.y*v2.z - v1.z*v2.y, 
                 v1.z*v2.x - v1.x*v2.z, 
                 v1.x*v2.y - v1.y*v2.x);
}

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = cross(s[0], s[1]);
    if (std::abs(u[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

Vec3f world2screen(Vec3f v, int width, int height) {
    return Vec3f(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}

void triangle(Vec3f *pts, Vec2i *texture_pts, float *zbuffer, TGAImage &image, Model* &model, float &intensity) { 
    int img_width = image.get_width();
    int img_height = image.get_height();
    int tex_width = model->diffusemap_width();
    int tex_height = model->diffusemap_height();
    Vec2f bboxmin(img_width-1,  img_height-1); 
    Vec2f bboxmax(0, 0); 
    Vec2f clamp(img_width-1, img_height-1); 
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::max(0.f,      std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }
    Vec3f P;
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
            Vec3f bc_screen  = barycentric(pts[0], pts[1], pts[2], P);
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            P.z = 0;
            for (int i=0; i<3; i++){
                P.z += pts[i][2]*bc_screen[i];
            }
            if (zbuffer[int(P.x+P.y*img_width)]<P.z) {
                zbuffer[int(P.x+P.y*img_width)] = P.z;
                TGAColor color = model->diffuse(
                    Vec2i((texture_pts[0].x)*bc_screen[0] + (texture_pts[1].x)*bc_screen[1] + (texture_pts[2].x)*bc_screen[2],
                    (texture_pts[0].y)*bc_screen[0] + (texture_pts[1].y)*bc_screen[1] + (texture_pts[2].y)*bc_screen[2])
                );
                image.set(P.x, P.y, color*intensity);
            }
        }
    }
}