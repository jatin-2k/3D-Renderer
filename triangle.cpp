#include "triangle.h"

void OldSchooltriangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    if (t0.y>t1.y) std::swap(t0, t1); 
    if (t0.y>t2.y) std::swap(t0, t2); 
    if (t1.y>t2.y) std::swap(t1, t2); 
    int total_height = t2.y-t0.y; 
    for (int y=t0.y; y<=t1.y; y++) { 
        int segment_height = t1.y-t0.y+1; 
        float alpha = (float)(y-t0.y)/total_height; 
        float beta  = (float)(y-t0.y)/segment_height; // div by 0
        Vec2i A = t0 + (t2-t0)*alpha; 
        Vec2i B = t0 + (t1-t0)*beta; 
        if (A.x>B.x) std::swap(A, B); 
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, y, color); 
        } 
    } 
    for (int y=t1.y; y<=t2.y; y++) { 
        int segment_height =  t2.y-t1.y+1; 
        float alpha = (float)(y-t0.y)/total_height; 
        float beta  = (float)(y-t1.y)/segment_height; // div by 0
        Vec2i A = t0 + (t2-t0)*alpha; 
        Vec2i B = t1 + (t2-t1)*beta; 
        if (A.x>B.x) std::swap(A, B); 
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, y, color);
        } 
    } 
}

Vec3f cross(const Vec3f &v1, const Vec3f &v2) {
    return Vec3f(v1.y*v2.z - v1.z*v2.y, 
                 v1.z*v2.x - v1.x*v2.z, 
                 v1.x*v2.y - v1.y*v2.x);
}

Vec3f barycentric(Vec2i *pts, Vec2i P) { 
    Vec3f u = cross(Vec3f(pts[2].x-pts[0].x, 
                          pts[1].x-pts[0].x, 
                          pts[0].x-P.x), 
                    Vec3f(pts[2].y-pts[0].y, 
                          pts[1].y-pts[0].y, 
                          pts[0].y-P.y));
    /* `pts` and `P` has integer value as coordinates
       so `abs(u[2])` < 1 means `u[2]` is 0, that means
       triangle is degenerate, 
       in this case returning something with negative coordinates */
    if (std::abs(u.z)<1) return Vec3f(-1,1,1);
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z); 
} 
 
void triangle(Vec2i *pts, TGAImage &image, TGAColor color) { 
    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1); 
    Vec2i bboxmax(0, 0); 
    Vec2i clamp(image.get_width()-1, image.get_height()-1); 
    for (int i=0; i<3; i++) { 
        bboxmin.x = std::max(0,        std::min(bboxmin.x, pts[i].x)); 
        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x)); 
        bboxmin.y = std::max(0,        std::min(bboxmin.y, pts[i].y)); 
        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y)); 
    } 
    Vec2i P; 
    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) { 
        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) { 
            Vec3f bc_screen  = barycentric(pts, P); 
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue; 
            image.set(P.x, P.y, color); 
        } 
    } 
} 

