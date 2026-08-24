#include "gl.h"
#include "model.h"
// #include <tuple>

constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor blue = {255, 128, 64, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

// void line(int ax, int ay, int bx, int by, TGAImage &image, const TGAColor
// &color)
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
//   return (0.5*((by - ay)*(ax + bx) + (cy - by)*(cx + bx) + (ay - cy)*(ax +
//   cx)));
// }

// void triangle(int ax, int ay, int az, int bx, int by, int bz, int cx, int cy,
// int cz, TGAImage &image, float* zbuffer, const TGAColor &color) {
// //颜色，深度等其他属性插值：1.先由点坐标与三角形三点的坐标出权重（面积之比） 2.再将三点对应的属性乘相应权重相加求出点的属性
//   int maxx = std::max(std::max(ax, bx), cx);
//   int maxy = std::max(std::max(ay, by), cy);
//   int minx = std::min(std::min(ax, bx), cx);
//   int miny = std::min(std::min(ay, by), cy);

//   double total_area = signed_area(ax, ay, bx, by, cx, cy);
//   if(total_area < 1) return;     //total_area < 1 可以防止total_area < 0
//   的背面面积，或total_area =
//   0使a、b、c计算时出错，或退化三角形（面积小于1像素的极小三角形

// #pragma omp parallel for       //OpenMP(多线程并行编程库)中专门用于自动将 for
// 循环拆分成多线程并行执行
//   for (int x = minx; x <= maxx; x++) {
//     for (int y = miny; y <= maxy; y++) {
//       double a = signed_area(x, y, bx, by, cx, cy) / total_area;
//       double b = signed_area(ax, ay, x, y, cx, cy) / total_area;
//       double c = signed_area(ax, ay, bx, by, x, y) / total_area;

//       if (a < 0 || b < 0 || c < 0)
//         continue;

//       float z = a * az + b * bz + c * cz;
//       int index = x + y * width; //将面中的每个像素一行一行排入数组中，下标 =
//       x + y * width; if (z > zbuffer[index]) {
//         zbuffer[index] = z;
//         image.set(x, y, color);
//       }
//     }
//   }
// }

// std::tuple<int,int,int> trans(vec3 po) {
//   return {((po.x + 1.0) * width / 2.0), ((po.y + 1.0) * height / 2.0), ((po.z
//   + 1.0) * 255 / 2.0)};
//   //映射: x(screen上的坐标) = (x(3d坐标) + 1) *
//   （Width/2）将3d坐标放大至适应具体像素的大小
//   //tuple: 元组,一次性存储任意数量、不同类型的数据,在头文件tuple中
//     }

// int main(int argc, char **argv)
// {

//   TGAImage framebuffer(width, height, TGAImage::RGB);
//   std::vector<float> zbuffer(width * height, -1e-10);
//   //初始化为极小数字,无穷小

//   model* model_ = new model("D:\\c_c++
//   vsc\\tinyrenderer\\obj\\african_head.obj"); std::cout << model_->nface() <<
//   std::endl;
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

//     triangle(ax,ay,az,bx,by,bz,cx,cy,cz,framebuffer,zbuffer.data(),rnd);
//     //vector.data()返回指向 vector 底层连续内存首元素的原生指针
//     }

//     framebuffer.write_tga_file("framebuffer1.tga");
//     delete (model_);
//   return 0;
// }

extern matrix<4, 4> Model, Perspective, View;
extern std::vector<double> zbuffer;

extern matrix<4, 4> Model_shadow, Perspective_shadow, View_shadow;
extern std::vector<double> zbuffer_shadow;

// class PhongShader : public Shader
// {
// private:
//   const class model &model_;
//   vec4 camera_pos;
//   TGAColor color = {};

// public:
//   PhongShader(const class model &m) : model_(m) {};

//   void setColor(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
//   {
//     color = {a, b, c, d};
//   }

//   virtual vec4 vertex(const int face_index, const int vertex_index) // 点着色器，处理单个点
//   {
//     vec4 clip_position;
//     auto [x, y, z] = model_.getvertex(face_index, vertex_index);
//     camera_pos = Model * vec4{x, y, z, 1};
//     clip_position = Perspective * camera_pos;

//     return clip_position;
//   }

//   virtual std::pair<bool, TGAColor> fragment(const vec3 &abc) const   //片元着色器
//   {
//     return {false, color};
//   }
// };

class ShadowShader : public Shader
{
private:
  const class model &model_;

public:
  ShadowShader(const class model &m) : model_(m) {}

  virtual vec4 vertex(const int face_index, const int vertex_index)
  {
    vec4 clip_position;
    auto [x, y, z] = model_.getvertex(face_index, vertex_index);
    clip_position = Perspective_shadow * Model_shadow * vec4{x, y, z, 1};

    return clip_position;
  }

  virtual std::pair<bool, TGAColor> fragment(const vec3 &abc) const
  {
    return {false, white};
  }
};

class PhongShader : public Shader
{
private:
  const class model &model_;
  const TGAImage &Image_shadow;
  vec3 camera_pos[3]; // 相机空间下坐标
  vec3 world_pos[3];  // 世界空间下坐标
  vec3 normal_cam[3]; // 相机空间下的法向量
  vec3 l;             // 指向光源的向量
  vec2 uv_pos[3];     // uv空间坐标

public:
  PhongShader(const class model &m, const TGAImage &image, const vec3 light) : model_(m), Image_shadow(image)
  {
    l = normalize((Model * vec4{light.x, light.y, light.z, 0.0}).getxyz());
  }

  virtual vec4 vertex(const int face_index, const int vertex_index) // 点着色器，处理单个点
  {
    vec4 clip_position;
    auto [x, y, z] = model_.getvertex(face_index, vertex_index);
    world_pos[vertex_index] = vec3{x, y, z};
    camera_pos[vertex_index] = (Model * vec4{x, y, z, 1}).getxyz();
    vec3 n = model_.getnormal(face_index, vertex_index);
    normal_cam[vertex_index] = (((inverse(Model)).transpose()) * vec4{n.x, n.y, n.z, 0.}).getxyz();
    uv_pos[vertex_index] = model_.getuv(face_index, vertex_index);
    clip_position = Perspective * Model * vec4{x, y, z, 1};

    return clip_position;
  }

  virtual std::pair<bool, TGAColor> fragment(const vec3 &abc) const // 片元着色器
  {
    // TGAColor AlbedoColor = white;
    // TGAColor color = AlbedoColor;
    //  vec3 n = normalize(cross((camera_pos[0] - camera_pos[1]), (camera_pos[0] - camera_pos[2]))); // 片元法向量
    vec3 n_world = normalize(abc[0] * normal_cam[0] + abc[1] * normal_cam[1] + abc[2] * normal_cam[2]);
    vec2 uv = abc[0] * uv_pos[0] + abc[1] * uv_pos[1] + abc[2] * uv_pos[2];
    vec3 n_tangent = normalize(model_.getnormal(uv));

    matrix<2, 3> E = {camera_pos[1] - camera_pos[0], camera_pos[2] - camera_pos[0]};
    matrix<2, 2> U = {uv_pos[1] - uv_pos[0], uv_pos[2] - uv_pos[0]};

    vec3 n = n_world;
    if (std::abs(det(U)) > 1e-8)
    {
      matrix<2, 3> TB = inverse(U) * E;
      matrix<3, 3> TBN = {normalize(TB[0]), normalize(TB[1]), n_world};
      n = normalize(TBN.transpose() * n_tangent);
    }

    vec3 r = normalize(2 * (l * n) * n - l);

    double x_camera = abc * vec3{camera_pos[0].x, camera_pos[1].x, camera_pos[2].x};
    double y_camera = abc * vec3{camera_pos[0].y, camera_pos[1].y, camera_pos[2].y};
    double z_camera = abc * vec3{camera_pos[0].z, camera_pos[1].z, camera_pos[2].z};

    double diff = std::max(0., l * n);
    double spec = std::pow(std::max(0., r * normalize(vec3{-x_camera, -y_camera, -z_camera})), 32); // std::pow(底数, 指数),#include <cmath>
    double spec_intensity = model_.getspec(uv);

    double ambient = 0.3;
    double diffuse = 0.4 * diff;
    double specular = 0.9 * spec_intensity * spec;

    TGAColor AlbedoColor = model_.getdiffuse(uv);
    TGAColor color = AlbedoColor;

    double x_world = abc * vec3{world_pos[0].x, world_pos[1].x, world_pos[2].x};
    double y_world = abc * vec3{world_pos[0].y, world_pos[1].y, world_pos[2].y};
    double z_world = abc * vec3{world_pos[0].z, world_pos[1].z, world_pos[2].z};
    vec4 light_clip = Perspective_shadow * Model_shadow * vec4{x_world, y_world, z_world, 1};
    vec2 light_screen = (View_shadow * (light_clip / light_clip.w)).getxy();
    constexpr double bias = 0.01; // 防止double计算时产生误差导致大小误判，从而阴影自遮挡
    constexpr int radius = 1;     // 采样半径
    int center_x = static_cast<int>(light_screen.x);
    int center_y = static_cast<int>(light_screen.y);
    double visibility = 0.0;
    int sample_count = 0;
    for (int x = -radius; x <= radius; x++)
    {
      for (int y = -radius; y <= radius; y++)
      {
        int fx = x + center_x;
        int fy = y + center_y;
        if (fx >= 0 && fx < Image_shadow.width() && fy >= 0 && fy < Image_shadow.height())
        {
          double depth = zbuffer_shadow[fx + fy * Image_shadow.width()];
          bool if_shadow = false;
          if_shadow = depth - bias > light_clip.z / light_clip.w;
          // 对比该点在光源视角下的实际距离与zbuffer中记录的距离，若zbuffer中z坐标值大于实际z坐标值，则该点在阴影中（z坐标值越大越靠前
          visibility += if_shadow ? 0.0 : 1.0;
          sample_count++;
        }
      }
    }

    if (sample_count == 0)
    {
      visibility = 1.0;
    }
    else
    {
      visibility /= sample_count;
    }
    double brightness = ambient + visibility * (diffuse + specular);
    for (int i = 0; i < 3; i++)
    {
      color[i] = AlbedoColor[i] * std::min(1., brightness); // 假设物体固有色与光的颜色相同
    }

    return {false, color};
  }
};

int main(int argc, char **argv)
{ // argc（Argument Count，参数个数）：当你从命令行（终端）启动程序时，系统会自动传入这个数字
  // argv 的全称是 Argument Vector（参数向量/参数字符串数组）,把你在命令行（终端）里敲下的那一长串命令，按空格拆开，一个一个存进这个数组里
  if (argc < 5 || (argc - 1) % 4 != 0)
  {
    std::cerr << "Usage: main.exe obj normal.tga diffuse.tga spec.tga [...]\n";
    return 1;
  }

  constexpr int width = 900;
  constexpr int height = 900;
  constexpr int width_shadow = 1024;
  constexpr int height_shadow = 1024;

  TGAImage framebuffer(width, height, TGAImage::RGB);
  TGAImage shadowbuffer(width_shadow, height_shadow, TGAImage::RGB);
  set_zbuffer(width, height, zbuffer);
  set_zbuffer(width_shadow, height_shadow, zbuffer_shadow);

  constexpr vec3 center{0, 0, 0};
  constexpr vec3 eye{-1, 0, 2};
  constexpr vec3 up{0, 1, 0};
  constexpr vec3 light_position{1, 1, 1};
  constexpr vec3 light_diretion{1, 1, 1};

  model(center, eye, up, Model); // 设置相机视角下的参数
  perspective(norm(eye - center), Perspective);
  view(width / 16, height / 16, width * 7 / 8, height * 7 / 8, View);

  model(center, light_position, up, Model_shadow); // 设置光源视角下的参数
  perspective(norm(light_position - center), Perspective_shadow);
  view(width_shadow / 16, height_shadow / 16, width_shadow * 7 / 8, height_shadow * 7 / 8, View_shadow);

  std::vector<class model> models;
  int model_count = (argc - 1) / 4;
  models.reserve(model_count); // vector.reserve(数量);预先分配容量，不会新增元素
  for (int j = 1; j < argc; j = j + 4)
  {
    models.emplace_back(argv[j], argv[j + 1], argv[j + 2], argv[j + 3]);
    // vector.emplace_back(构造函数参数...);在 vector 末尾直接构造并加入一个对象
  }

  for (const class model &model_ : models)
  {
    ShadowShader shader_shadow(model_);
    for (int i = 0; i < model_.nface(); i++)
    {
      Triangle clip_shadow = {shader_shadow.vertex(i, 0), shader_shadow.vertex(i, 1), shader_shadow.vertex(i, 2)};
      rasterize(clip_shadow, shadowbuffer, shader_shadow, View_shadow, zbuffer_shadow);
    }
  }

  for (const class model &model_ : models)
  {
    PhongShader shader(model_, shadowbuffer, light_diretion);
    for (int i = 0; i < model_.nface(); i++)
    {
      // shader.setColor(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255);
      Triangle clip = {shader.vertex(i, 0), shader.vertex(i, 1), shader.vertex(i, 2)};
      rasterize(clip, framebuffer, shader, View, zbuffer);
    }
  }

  framebuffer.write_tga_file("framebuffer1.tga");

  return 0;
};