#include "model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

model::model(const std::string &filename_obj, const std::string &filename_tex, const std::string &filename_diff)
{
  std::ifstream in;
  in.open(filename_obj);
  if (in.fail())
  {
    std::cout << "open file fail" << std::endl;
    return;
  }

  std::string line;
  while (!in.eof())
  {
    std::getline(in, line);
    std::istringstream iss(line); // istringstream 包含在sstream中，把一行文本，变成可以用 >> 拆分读取的字符串流，专门用来解析带空格的一行数据。
    std::string first;

    if (!line.compare(0, 2, "v "))
    { // string1.compare(string2)函数  比较string1和string2，若二者相等则返回0
      iss >> first;
      vec3 point_;
      iss >> point_.x >> point_.y >> point_.z;
      vertex.push_back(point_);
    }
    else if (!line.compare(0, 3, "vn "))
    {
      iss >> first;
      vec3 normal_;
      iss >> normal_.x >> normal_.y >> normal_.z;
      normal.push_back(normal_);
    }
    else if (!line.compare(0, 3, "vt "))
    {
      iss >> first;
      vec2 texture_;
      iss >> texture_.x >> texture_.y;
      texture.push_back(texture_);
    }
    else if (!line.compare(0, 2, "f "))
    {
      int index;
      std::vector<int> v;
      std::vector<int> n;
      std::vector<int> t;
      iss >> first;
      std::string buffer;
      while (iss >> buffer)
      {
        int first = buffer.find_first_of("/"); // 找第一个“/”的位置,s.find_first_of('/', pos) 的意思是：从下标 pos 开始往后扫描
        int second = buffer.find_first_of("/", first + 1);
        index = stoi(buffer.substr(0, first)); // 保留第一个数, stoi => string to int
        index--;
        v.push_back(index);
        index = stoi(buffer.substr(first + 1, second - first - 1));
        index--;
        t.push_back(index);
        index = stoi(buffer.substr(second + 1));
        index--;
        n.push_back(index);
      }
      face_v.push_back(v);
      face_t.push_back(t);
      face_n.push_back(n);
    }
  }

  if (!load_tex_map(filename_tex))
  {
    std::cerr << "failed to load normal map\n";
    // std::cerr << 是用来向控制台（终端）输出错误信息或警告信息的
  }

  if (!load_dif_map(filename_diff))
  {
    std::cerr << "failed to load diffuse map\n";
  }
}