#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

template<int n> struct vec {
    double data[n] = {0};
    double& operator[](const int i)       { assert(i>=0 && i<n); return data[i]; }       //assert()主动检查一个条件必须成立，如果不成立，程序立刻崩溃并报错,不要在 assert 里写类似i++的业务代码，不会使i+1
    double  operator[](const int i) const { assert(i>=0 && i<n); return data[i]; }
};

template<int n> std::ostream& operator<<(std::ostream& out, const vec<n>& v) {
    for (int i=0; i<n; i++) out << v[i] << " ";
    return out;
}

template <int n> double operator*(const vec<n> &vec1, const vec<n> &vec2) {
  double result;
  for (int i = 0; i < n; i++) {
    result += vec1[i] * vec2[i];
  }
  return result;
}

template<> struct vec<3> {
    double x = 0, y = 0, z = 0;
    double& operator[](const int i)       { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
    double  operator[](const int i) const { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
};

typedef vec<3> vec3;

template<> struct vec<2> {
    double x = 0, y = 0;
    double& operator[](const int i)       { assert(i>=0 && i<2); return i ? y : x; }
    double  operator[](const int i) const { assert(i>=0 && i<2); return i ? y : x; }
};

typedef vec<2> vec2;

template<> struct vec<4> {
    double x = 0, y = 0, z = 0, w = 0;
    double& operator[](const int i)       { assert(i>=0 && i<4); return i ? (1==i ? y : (2==i ? z : w)) : x; }
    double  operator[](const int i) const { assert(i>=0 && i<4); return i ? (1==i ? y : (2==i ? z : w)) : x; }
};

typedef vec<4> vec4;

template <int r, int c> struct matrix {
  vec<c> row[r];

  
}