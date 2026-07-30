#include "tgaimage.h"
#include "model.h"
#include <iostream>
//#include <tuple>

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

// void line(int ax, int ay, int bx, int by, TGAImage &image, const TGAColor &color)
// {
//   bool steep = (std::abs(ax - bx) < std::abs(ay - by));
//   if (steep){
//         std::swap(ax, ay);
//         std::swap(bx,by);
//   }
//   if (ax > bx) {
//     std::swap(ax, bx);
//     std::swap(ay, by);
//   }
//   int error = 0;
//   int y = ay;
//   for (int x = ax; x <= bx; x++) {
//     if (steep) 
//       image.set(y, x, color);
//     else
//       image.set(x, y, color);
//     error += 2 * std::abs(by - ay);
//     if (error > bx - ax) {
//       y += ay < by ? 1 : -1;
//       error -= 2 * (bx - ax);
//    }   
//   }
// }

// double signed_area(int ax, int ay, int bx, int by, int cx, int cy) {
//   return (0.5*((by - ay)*(ax + bx) + (cy - by)*(cx + bx) + (ay - cy)*(ax + cx)));
// }

// void triangle(int ax, int ay, int az, int bx, int by, int bz, int cx, int cy, int cz, TGAImage &image, float* zbuffer, const TGAColor &color) {
// //颜色，深度等其他属性插值：1.先由点坐标与三角形三点的坐标出权重（面积之比） 2.再将三点对应的属性乘相应权重相加求出点的属性
//   int maxx = std::max(std::max(ax, bx), cx);
//   int maxy = std::max(std::max(ay, by), cy);
//   int minx = std::min(std::min(ax, bx), cx);
//   int miny = std::min(std::min(ay, by), cy);

//   double total_area = signed_area(ax, ay, bx, by, cx, cy);
//   if(total_area < 1) return;     //total_area < 1 可以防止total_area < 0 的背面面积，或total_area = 0使a、b、c计算时出错，或退化三角形（面积小于1像素的极小三角形
  
// #pragma omp parallel for       //OpenMP(多线程并行编程库)中专门用于自动将 for 循环拆分成多线程并行执行
//   for (int x = minx; x <= maxx; x++) {
//     for (int y = miny; y <= maxy; y++) {
//       double a = signed_area(x, y, bx, by, cx, cy) / total_area;
//       double b = signed_area(ax, ay, x, y, cx, cy) / total_area;
//       double c = signed_area(ax, ay, bx, by, x, y) / total_area;

//       if (a < 0 || b < 0 || c < 0)
//         continue;

//       float z = a * az + b * bz + c * cz;
//       int index = x + y * width;              //将面中的每个像素一行一行排入数组中，下标 = x + y * width;
//       if (z > zbuffer[index]) {
//         zbuffer[index] = z;
//         image.set(x, y, color);
//       }
//     }
//   }
// }
    
// std::tuple<int,int,int> trans(vec3 po) {
//   return {((po.x + 1.0) * width / 2.0), ((po.y + 1.0) * height / 2.0), ((po.z + 1.0) * 255 / 2.0)};
//   //映射: x(screen上的坐标) = (x(3d坐标) + 1) * （Width/2）将3d坐标放大至适应具体像素的大小
//   //tuple: 元组,一次性存储任意数量、不同类型的数据,在头文件tuple中
//     }

// int main(int argc, char **argv)
// {

//   TGAImage framebuffer(width, height, TGAImage::RGB);
//   std::vector<float> zbuffer(width * height, -1e-10);           //初始化为极小数字,无穷小
  
//   model* model_ = new model("D:\\c_c++  vsc\\tinyrenderer\\obj\\african_head.obj");
//   std::cout << model_->nface() << std::endl;
//   // for (int i = 0; i < model_->nface(); i++) {               //线条画
//   //   std::vector<int> face_ = model_->getface(i);
//   //   for (int j = 0; j < 3; j++) {
//   //     point point1 = model_->getvertex(face_[j]);
//   //     point point2 = model_->getvertex(face_[(j + 1) % 3]);

//   //     auto [x1, y1] = trans(point1);
//   //     auto [x2,y2] = trans(point2);

//   //     line(x1,y1,x2,y2,framebuffer,red);
//   //     }
//   //   }

//   // for (int i = 0; i < model_->nface(); i++) {             //填充三角形
//   //   std::vector<int> face_ = model_->getface(i);

//   //   auto [ax, ay] = trans(model_->getvertex(face_[0]));
//   //   auto [bx, by] = trans(model_->getvertex(face_[1]));
//   //   auto [cx, cy] = trans(model_->getvertex(face_[2]));

//   //   triangle(ax,ay,0,bx,by,0,cx,cy,0,framebuffer,red,blue,white);
//   //   }

//   for (int i = 0; i < model_->nface(); i++) {
//     std::vector<int> face_ = model_->getface(i);

//     auto [ax, ay, az] = trans(model_->getvertex(face_[0]));
//     auto [bx, by, bz] = trans(model_->getvertex(face_[1]));
//     auto [cx, cy, cz] = trans(model_->getvertex(face_[2]));

//     TGAColor rnd;
//     for (int c=0; c<3; c++) rnd[c] = std::rand()%255;

//     triangle(ax,ay,az,bx,by,bz,cx,cy,cz,framebuffer,zbuffer.data(),rnd);              //vector.data()返回指向 vector 底层连续内存首元素的原生指针
//     }

//     framebuffer.write_tga_file("framebuffer1.tga");
//     delete (model_);
//   return 0;
// }

matrix<4, 4> Model;
matrix<4, 4> Perspective;
matrix<4, 4> View;

void model(const vec3 center, const vec3 eye, const vec3 up) {              //转换至相机坐标系
  vec3 n = normalize(eye - center);
  vec3 l = normalize(cross(up, n));
  vec3 m = normalize(cross(n, l));

  Model = matrix<4, 4>{{{l.x, l.y, l.z, 0},
                        {m.x, m.y, m.z, 0},
                        {n.x, n.y, n.z, 0},
                        {0, 0, 0, 1}}} *
          matrix<4, 4>{{{1, 0, 0, -center.x},
                        {0, 1, 0, -center.y},
                        {0, 0, 1, -center.z},
                        {0, 0, 0, 1}}};
}

void perspective(const double f) {          //透视矩阵
  Perspective = matrix<4, 4>{
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, -1 / f, 1}}};
}

void view(const int x, const int y, const int w, const int h) {        //视图矩阵
  View = matrix<4, 4>{{{w / 2., 0, 0, x + w / 2.},
                       {0, h / 2., 0, y + h / 2.},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}}};
}

void rasterize(vec4 clip[3], TGAImage &image, std::vector<float> &zbuffer,
               const TGAColor &color) {  //clip[3]为三角形三条边. 参数使用引用可以改变原始数据，若不使用引用则会拷贝副本，修改的也是副本数据
  vec4 ndc[3] = {clip[0] / clip[0].w, clip[1] / clip[1].w, clip[2] / clip[2].w};    //除以w将原图形放入ndc坐标中同时实现透视坐标的转换，再进行视图变换以防坐标与屏幕不适配
  vec2 screen[3] = {(View * ndc[0]).getxy(), (View * ndc[1]).getxy(),
                    (View * ndc[2]).getxy()};

  matrix<3, 3> ABC = matrix<3, 3>{{{screen[0].x, screen[1].x, screen[2].x},      //面积矩阵，其行列式即为三角形的有方向面积*2
                                   {screen[0].y, screen[1].y, screen[2].y},
                                   {1, 1, 1}}};
  if (det(ABC) / 2. < 1)
    return;

  int maxx = std::max(std::max(screen[0].x, screen[1].x), screen[2].x);
  int minx = std::min(std::min(screen[0].x, screen[1].x), screen[2].x);
  int maxy = std::max(std::max(screen[0].y, screen[1].y), screen[2].y);
  int miny = std::min(std::min(screen[0].y, screen[1].y), screen[2].y);

#pragma omp parallel for // OpenMP(多线程并行编程库)中专门用于自动将 for
                         // 循环拆分成多线程并行执行
  for (int x = std::max(minx,0); x <= std::min(maxx,image.width() - 1); x++) {        //std::max(minx,0)，std::min(maxx,image.width() - 1)：防止当模型太大超出屏幕时，超出屏幕部分造成内存越界
    for (int y = std::max(miny, 0);
         y <= std::min(maxy, image.height() - 1); y++) {
      vec3 abc =          //权重
          inverse(ABC) * vec3{static_cast<double>(x), static_cast<double>(y),1}; // static_cast<double>(x)将x安全地转换为double
      if (abc.x < 0 || abc.y < 0 || abc.z < 0)         //小于0说明该面为模型的背面，不用画
        continue;

      double z = abc * vec3{ndc[0].z, ndc[1].z, ndc[2].z};
      int index = x + y * image.width();
      if (z > zbuffer[index]) {
        zbuffer[index] = z;
        image.set(x,y,color);
      }
    }
  }
}

int main(int argc, char **argv) {      //argc（Argument Count，参数个数）：当你从命令行（终端）启动程序时，系统会自动传入这个数字
  //argv 的全称是 Argument Vector（参数向量/参数字符串数组）,把你在命令行（终端）里敲下的那一长串命令，按空格拆开，一个一个存进这个数组里
  if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
        return 1;
  }
  
  constexpr int width = 800;
  constexpr int height = 800;

  TGAImage framebuffer(width, height, TGAImage::RGB);
  std::vector<float> zbuffer(width * height, -std::numeric_limits<double>::max());       // 初始化为极小数字,无穷小，-std::numeric_limits<double>::max() 代表的是 double 浮点数能表示的“最小负数”（也就是绝对值最大的负值）

  constexpr vec3 center{0, 0, 0};
  constexpr vec3 eye{-1,0,2};
  constexpr vec3 up{0, 1, 0};

  model(center, eye, up);
  perspective(norm(eye - center));
  view(width / 16, height / 16, width * 7 / 8, height * 7 / 8);

  for (int j = 1; j < argc; j++) {
    class model *model_ = new class model(argv[j]);
    for (int i = 0; i < model_->nface(); i++) {
      std::vector<int> face_ = model_->getface(i);

      vec4 clip[3];
      for (int k = 0; k < 3; k++) {
        auto [x, y, z] = model_->getvertex(face_[k]);
        clip[k] = Perspective * Model * vec4{x, y, z, 1};
      }

      rasterize(clip, framebuffer, zbuffer, red);
    }
    delete model_;
  }

  framebuffer.write_tga_file("framebuffer1.tga");

  return 0;
}