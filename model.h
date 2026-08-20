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

public:
  model(const std::string &filename_obj, const std::string &filename_tga);
  int nvertex() { return vertex.size(); }
  int nface() { return face_v.size(); }
  vec3 getvertex(const int i) const { return vertex[i]; }
  vec3 getvertex(const int face_index, const int vertex_index) const { return vertex[face_v[face_index][vertex_index]]; }

  vec3 getnormal(const int i) const { return normal[i]; }
  vec3 getnormal(const int face_index, const int vertex_index) const { return normal[face_n[face_index][vertex_index]]; }
  vec3 getnormal(const vec2 uv) const
  { // 通过法线贴图解析法线
    int x = static_cast<int>(uv[0] * tex_map.width());
    int y = static_cast<int>((1.0 - uv[1]) * tex_map.height());
    // UV 坐标原点不一致，需翻转y坐标

    TGAColor c = tex_map.get(x, y);

    vec3 n;
    n.x = (double)(c[0] / 255.0) * 2 - 1.;
    n.y = (double)(c[1] / 255.0) * 2 - 1.;
    n.z = (double)(c[2] / 255.0) * 2 - 1.;

    return n;
  }

  vec2 getuv(const int face_index, const int vertex_index) const { return texture[face_t[face_index][vertex_index]]; }
  std::vector<int> getface(const int i) const { return face_v[i]; }

  bool load_map(const std::string &filename) { return tex_map.read_tga_file(filename); }
};