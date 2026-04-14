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
  vec3 getvertex(int i) const { return vertex[i]; }
  std::vector<int> getface(int i) const { return face[i]; }
};