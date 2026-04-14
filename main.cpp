#include "tgaimage.h"
#include "model.h"
#include <iostream>
#include <tuple>

constexpr int width  = 800;
constexpr int height = 800;

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &image, const TGAColor &color)
{
  bool steep = (std::abs(ax - bx) < std::abs(ay - by));
  if (steep){
        std::swap(ax, ay);
        std::swap(bx,by);
  }
  if (ax > bx) {
    std::swap(ax, bx);
    std::swap(ay, by);
  }
  int error = 0;
  int y = ay;
  for (int x = ax; x <= bx; x++) {
    if (steep) 
      image.set(y, x, color);
    else
      image.set(x, y, color);
    error += 2 * std::abs(by - ay);
    if (error > bx - ax) {
      y += ay < by ? 1 : -1;
      error -= 2 * (bx - ax);
   }   
  }
}

double signed_area(int ax, int ay, int bx, int by, int cx, int cy) {
  return (0.5*((by - ay)*(ax + bx) + (cy - by)*(cx + bx) + (ay - cy)*(ax + cx)));
}

void triangle(int ax, int ay, int az, int bx, int by, int bz, int cx, int cy, int cz, TGAImage &image, TGAImage& zbuffer, const TGAColor &colora, const TGAColor &colorb, const TGAColor &colorc) {
//颜色，深度等其他属性插值：1.先由点坐标与三角形三点的坐标出权重（面积之比） 2.再将三点对应的属性乘相应权重相加求出点的属性
  int maxx = std::max(std::max(ax, bx), cx);
  int maxy = std::max(std::max(ay, by), cy);
  int minx = std::min(std::min(ax, bx), cx);
  int miny = std::min(std::min(ay, by), cy);

  double total_area = signed_area(ax, ay, bx, by, cx, cy);
  if(total_area < 1) return;     //total_area < 1 可以防止total_area < 0 的背面面积，或total_area = 0使a、b、c计算时出错，或退化三角形（面积小于1像素的极小三角形
#pragma omp parallel for       //OpenMP(多线程并行编程库)中专门用于自动将 for 循环拆分成多线程并行执行
  for (int x = minx; x <= maxx; x++) {
    for (int y = miny; y <= maxy; y++) {
      double a = signed_area(x, y, bx, by, cx, cy) / total_area;
      double b = signed_area(ax, ay, x, y, cx, cy) / total_area;
      double c = signed_area(ax, ay, bx, by, x, y) / total_area;

      if (a < 0 || b < 0 || c < 0)
        continue;
      std::uint8_t color0 = a * colora[0] + b * colorb[0] + c * colorc[0];
      std::uint8_t color1 = a * colora[1] + b * colorb[1] + c * colorc[1];
      std::uint8_t color2 = a * colora[2] + b * colorb[2] + c * colorc[2];
      
      std::uint8_t z = static_cast<std::uint8_t>(a * az + b * bz + c * cz);        //static_cast<typename>() 静态类型转换,显式类型转换,编译期检查
      if (z <= zbuffer.get(x, y)[0])
        continue;
      image.set(x, y, {color0, color1, color2});
      zbuffer.set(x, y, {z});
      }
    }
    }
    
std::tuple<int,int,int> trans(vec3 po) {
  return {((po.x + 1.0) * width / 2.0), ((po.y + 1.0) * height / 2.0), ((po.z + 1.0) * 255 / 2.0)};
  //映射: x(screen上的坐标) = (x(3d坐标) + 1) * （Width/2）将3d坐标放大至适应具体像素的大小
  //tuple: 元组,一次性存储任意数量、不同类型的数据,在头文件tuple中
    }

int main(int argc, char **argv)
{

  TGAImage framebuffer(width, height, TGAImage::RGB);
  TGAImage zbuffer(width, height, TGAImage::RGB);
  
  model* model_ = new model("D:\\c_c++  vsc\\tinyrenderer\\obj\\african_head.obj");
  std::cout << model_->nface() << std::endl;
  // for (int i = 0; i < model_->nface(); i++) {               //线条画
  //   std::vector<int> face_ = model_->getface(i);
  //   for (int j = 0; j < 3; j++) {
  //     point point1 = model_->getvertex(face_[j]);
  //     point point2 = model_->getvertex(face_[(j + 1) % 3]);

  //     auto [x1, y1] = trans(point1);
  //     auto [x2,y2] = trans(point2);

  //     line(x1,y1,x2,y2,framebuffer,red);
  //     }
  //   }

  // for (int i = 0; i < model_->nface(); i++) {             //填充三角形
  //   std::vector<int> face_ = model_->getface(i);

  //   auto [ax, ay] = trans(model_->getvertex(face_[0]));
  //   auto [bx, by] = trans(model_->getvertex(face_[1]));
  //   auto [cx, cy] = trans(model_->getvertex(face_[2]));

  //   triangle(ax,ay,0,bx,by,0,cx,cy,0,framebuffer,red,blue,white);
  //   }

  for (int i = 0; i < model_->nface(); i++) {
    std::vector<int> face_ = model_->getface(i);

    auto [ax, ay, az] = trans(model_->getvertex(face_[0]));
    auto [bx, by, bz] = trans(model_->getvertex(face_[1]));
    auto [cx, cy, cz] = trans(model_->getvertex(face_[2]));

    triangle(ax,ay,az,bx,by,bz,cx,cy,cz,framebuffer,zbuffer,red,blue,white);
    }

    framebuffer.write_tga_file("framebuffer1.tga");
    zbuffer.write_tga_file("zbuffer.tga");
    delete(model_);
  return 0;
}