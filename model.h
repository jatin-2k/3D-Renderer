#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "provided/code/tgaimage.h"
#include "provided/code/geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<Vec3i> > faces_; // attention, this Vec3i means vertex/uv/normal
	std::vector<Vec3f> norms_;
	std::vector<Vec2f> uv_;
	TGAImage diffusemap_;
	void load_texture(std::string filename, const char *suffix, TGAImage &img);
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	Vec2i uv(int iface, int nvert);
	TGAColor diffuse(Vec2i uv);
	int diffusemap_height(){ return diffusemap_.get_height(); }
	int diffusemap_width(){ return diffusemap_.get_width(); }
	std::vector<int> face(int idx);
};

#endif //__MODEL_H__