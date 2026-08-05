#pragma once
#include <utility>
#include "tgaimage.h"
#include "geometry.h"

void set_zbuffer(const int width, const int height);
void model(const vec3 center, const vec3 eye, const vec3 up);
void perspective(const double f);
void view(const int x, const int y, const int w, const int h);

class Shader {        //着色器
public:
  virtual ~Shader() {};
  virtual std::pair<bool, TGAColor> fragment(const vec3 &abc) const = 0;
  //std::pair<T1, T2> name;<utility> 头文件中，把两个不同或相同类型的数据打包组合在一起，当成一个整体来使用，T1用 name.first 访问，T2用 name.second 访问
};

typedef vec4 Triangle[3];
void rasterize(const Triangle &clip, TGAImage &image, const Shader &shader);

