#pragma once
#include <string>
#include "tgaimage.h"
#include "geometry.h"

class model
{
private:
  std::vector<vec3> vertex = {};             // 储存点信息
  std::vector<std::vector<int>> face_v = {}; // 存储面的点信息
  std::vector<vec3> normal = {};             // 存储每个点的法线信息
  std::vector<std::vector<int>> face_n = {};
  std::vector<vec2> texture = {}; // 存储纹理信息
  std::vector<std::vector<int>> face_t = {};
  TGAImage tex_map = {};
  TGAImage diffuse_map = {};
  TGAImage spec_map = {};

public:
  model(const std::string &filename_obj, const std::string &filename_tex, const std::string &filename_diff, const std::string &filename_spec);
  int nvertex() { return vertex.size(); }
  int nface() { return face_v.size(); }
  TGAColor getcolor(const vec2 uv, const TGAImage &map) const;
  vec3 getvertex(const int i) const;
  vec3 getvertex(const int face_index, const int vertex_index) const;
  vec3 getnormal(const int i) const;
  vec3 getnormal(const int face_index, const int vertex_index) const;
  vec3 getnormal(const vec2 uv) const;
  TGAColor getdiffuse(const vec2 uv) const;
  double getspec(const vec2 uv) const;
  vec2 getuv(const int face_index, const int vertex_index) const;
  std::vector<int> getface(const int i) const;
  bool load_map(const std::string &filename, TGAImage &map) { return map.read_tga_file(filename); }
};