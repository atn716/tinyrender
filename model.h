#pragma once
#include <string>
#include <vector>
#include "geometry.h"

class model {
private:
  std::vector<vec3> vertex;    //储存点信息
  std::vector<std::vector<int>> face;

public:
  model(const std::string filename);
  int nvertex() { return vertex.size(); }
  int nface() { return face.size(); }
  vec3 getvertex(const int i) const { return vertex[i]; }
  vec3 getvertex(const int face_index, const int vertex_index) const { return vertex[face[face_index][vertex_index]]; }
  std::vector<int> getface(const int i) const { return face[i]; }
};