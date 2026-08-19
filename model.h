#pragma once
#include <string>
#include <vector>
#include "geometry.h"

class model
{
private:
  std::vector<vec3> vertex;             // 储存点信息
  std::vector<std::vector<int>> face_v; // 存储面的点信息
  std::vector<vec3> normal;             // 存储每个点的法线信息
  std::vector<std::vector<int>> face_n;
  std::vector<vec3> texture; // 存储纹理信息
  std::vector<std::vector<int>> face_t;

public:
  model(const std::string filename);
  int nvertex() { return vertex.size(); }
  int nface() { return face_v.size(); }
  vec3 getvertex(const int i) const { return vertex[i]; }
  vec3 getvertex(const int face_index, const int vertex_index) const { return vertex[face_v[face_index][vertex_index]]; }
  vec3 getnormal(const int i) const { return normal[i]; }
  vec3 getnormal(const int face_index, const int vertex_index) const { return normal[face_n[face_index][vertex_index]]; }
  std::vector<int> getface(const int i) const { return face_v[i]; }
};