#include "gl.h"

matrix<4, 4> Model;
matrix<4, 4> Perspective;
matrix<4, 4> View;
std::vector<double> zbuffer;

matrix<4, 4> Model_shadow;
matrix<4, 4> Perspective_shadow;
matrix<4, 4> View_shadow;
std::vector<double> zbuffer_shadow;

void set_zbuffer(const int width, const int height, std::vector<double> &depth_buffer)
{
  depth_buffer = std::vector<double>(width * height, -std::numeric_limits<double>::max()); // 初始化为极小数字,无穷小，-std::numeric_limits<double>::max() 代表的是 double 浮点数能表示的“最小负数”（也就是绝对值最大的负值）
}

void model(const vec3 center, const vec3 eye, const vec3 up, matrix<4, 4> &Model_matrix)
{ // 转换至相机坐标系
  vec3 n = normalize(eye - center);
  vec3 l = normalize(cross(up, n));
  vec3 m = normalize(cross(n, l));

  Model_matrix = matrix<4, 4>{{{l.x, l.y, l.z, 0},
                               {m.x, m.y, m.z, 0},
                               {n.x, n.y, n.z, 0},
                               {0, 0, 0, 1}}} *
                 matrix<4, 4>{{{1, 0, 0, -center.x},
                               {0, 1, 0, -center.y},
                               {0, 0, 1, -center.z},
                               {0, 0, 0, 1}}};
}

void perspective(const double f, matrix<4, 4> &Perspective_matrix)
{ // 透视矩阵
  Perspective_matrix = matrix<4, 4>{
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, -1 / f, 1}}};
}

void view(const int x, const int y, const int w, const int h, matrix<4, 4> &View_matrix)
{ // 视图矩阵
  View_matrix = matrix<4, 4>{{{w / 2., 0, 0, x + w / 2.},
                              {0, h / 2., 0, y + h / 2.},
                              {0, 0, 1, 0},
                              {0, 0, 0, 1}}};
}

void rasterize(const Triangle &clip, TGAImage &image, const Shader &shader, const matrix<4, 4> &View_matrix, std::vector<double> &depth_buffer)
{ // 基类引用或指针可以指向派生类
  // clip[3]为三角形三个顶点. 参数使用引用可以改变原始数据，若不使用引用则会拷贝副本，修改的也是副本数据
  vec4 ndc[3] = {clip[0] / clip[0].w, clip[1] / clip[1].w, clip[2] / clip[2].w}; // 除以w将原图形放入ndc坐标中同时实现透视坐标的转换，再进行视图变换以防坐标与屏幕不适配
  vec2 screen[3] = {(View_matrix * ndc[0]).getxy(), (View_matrix * ndc[1]).getxy(),
                    (View_matrix * ndc[2]).getxy()};

  matrix<3, 3> ABC = matrix<3, 3>{{{screen[0].x, screen[1].x, screen[2].x}, // 面积矩阵，其行列式即为三角形的有方向面积*2
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
  for (int x = std::max(minx, 0); x <= std::min(maxx, image.width() - 1); x++)
  { // std::max(minx,0)，std::min(maxx,image.width() - 1)：防止当模型太大超出屏幕时，超出屏幕部分造成内存越界
    for (int y = std::max(miny, 0);
         y <= std::min(maxy, image.height() - 1); y++)
    {
      vec3 screen_abc =                                                           // 权重
          inverse(ABC) * vec3{static_cast<double>(x), static_cast<double>(y), 1}; // static_cast<double>(x)将x安全地转换为double
      if (screen_abc.x < 0 || screen_abc.y < 0 || screen_abc.z < 0)               // 小于0说明该面为模型的背面，不用画
        continue;

      vec3 abc = {screen_abc.x / clip[0].w, screen_abc.y / clip[1].w, screen_abc.z / clip[2].w};
      abc = abc / (abc.x + abc.y + abc.z);

      double z = screen_abc * vec3{ndc[0].z, ndc[1].z, ndc[2].z};
      int index = x + y * image.width();
      if (z > depth_buffer[index])
      {
        auto [discard, color] = shader.fragment(abc);
        if (discard)
          continue;

        double alpha = color[3] / 255.0;

        if (alpha >= 1.)
        { // 不透明：覆盖颜色，并写入深度
          depth_buffer[index] = z;
          image.set(x, y, color);
        }
        else
        { // 透明：与屏幕当前颜色混合，但不写入深度
          TGAColor final_color = image.get(x, y);

          for (int i = 0; i < 3; i++)
          {
            final_color[i] = static_cast<std::uint8_t>(color[i] * alpha + final_color[i] * (1. - alpha));
          }
          final_color[3] = 255.0;
          image.set(x, y, final_color);
        }
      }
    }
  }
}