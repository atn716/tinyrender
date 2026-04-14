#include "model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

model::model(const std::string filename) {
  std::ifstream in;
  in.open(filename);
  if (in.fail()) {
    std::cout << "open file fail" << std::endl;
    return;
  }
    
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line);           //istringstream 包含在sstream中，把一行文本，变成可以用 >> 拆分读取的字符串流，专门用来解析带空格的一行数据。
    char first;

    if (!line.compare(0, 2, "v ")) {        //string1.compare(string2)函数  比较string1和string2，若二者相等则返回0
      iss >> first;
      vec3 point_;
      iss >> point_.x >> point_.y >> point_.z;
      vertex.push_back(point_);
    }
    else if (!line.compare(0, 2, "f ")) {
      int index;
      std::vector<int> face_ver;
      iss >> first;
      std::string buffer;
      while (iss >> buffer) {
        int i = buffer.find_first_of("/");    // 找第一个“/”的位置
        index = stoi(buffer.substr(0, i));     // 保留第一个数, stoi => string to int
        index--;
        face_ver.push_back(index);
      }
      face.push_back(face_ver);
      }
  }
    }