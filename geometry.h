#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

template <int n> struct vec {
    double data[n] = {0};
    double& operator[](const int i)       { assert(i>=0 && i<n); return data[i]; }       //在<cassert>中assert()主动检查一个条件必须成立，如果不成立，程序立刻崩溃并报错,不要在 assert 里写类似i++的业务代码，不会使i+1
    double  operator[](const int i) const { assert(i>=0 && i<n); return data[i]; }
};

template <int n> std::ostream& operator<<(std::ostream& out, const vec<n>& v) {
    for (int i=0; i<n; i++) out << v[i] << " ";
    return out;
}

template <int n> vec<n> operator+(const vec<n> &vec1, const vec<n> &vec2) {
    vec<n> result;
    for (int i = 0; i < n; i++) {
      result[i] = vec1[i] + vec2[i];
    }
    return result;
}

template <int n> vec<n> operator-(const vec<n> &vec1, const vec<n> &vec2) {
    vec<n> result;
    for (int i = 0; i < n; i++) {
      result[i] = vec1[i] - vec2[i];
    }
    return result;
}

template <int n> vec<n> operator*(const double &num, const vec<n> &v) {
    vec<n> result;
    for (int i = 0; i < n; i++) {
      result[i] = num * v[i];
    }
    return result;
}

template <int n> vec<n> operator/(const vec<n> &v, const double &num) {
    vec<n> result;
    for (int i = 0; i < n; i++) {
      result[i] = v[i]/num;
    }
    return result;
}

template <int n> double operator*(const vec<n> &vec1, const vec<n> &vec2) {        //向量乘法
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

template <int n> double norm(const vec<n> &v) { return std::sqrt(v * v); }

template <int n> vec<n> normalize(const vec<n> &v) { return v / norm(v); }

template<> struct vec<3> {
    double x = 0, y = 0, z = 0;
    double& operator[](const int i)       { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
    double  operator[](const int i) const { assert(i>=0 && i<3); return i ? (1==i ? y : z) : x; }
};

typedef vec<3> vec3;

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
          v1.x * v2.y - v1.y * v2.x};
}
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

    vec<c>& operator[](const int i)       { assert(i>=0 && i<r); return row[i]; }
    const vec<c>& operator[](const int i) const { assert(i>=0 && i<r); return row[i]; }

    vec<r> getcolumn(const int j) const {
      assert(j >= 0 && j < c);
      vec<r> temp;
      for (int i = 0; i < r; i++) {
        temp[i] = row[i][j];
      }
      return temp;
    }

    void setcolumn(const int j, vec<r> buffer) {
      assert(j >= 0 && j < c);
      for (int i = 0; i < r; i++) {
        row[i][j] = buffer[i];
      }
    }

    matrix<c, r> transpose() const {
      matrix<c, r> temp;
      for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            temp[i][j] = row[j][i];
        }
      }
      return temp;
    }
};

template <int n> matrix<n, n> identity() {
    matrix<n, n> result;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result[i][j] = (i == j);
      }
    }
    return result;
}

template <int r, int c>
matrix<r, c> operator+(const matrix<r, c> &mat1, const matrix<r, c> &mat2) {
    matrix<r, c> temp;
    for (int i = 0; i < r; i++) {
      temp[i] = mat1[i] + mat2[i];
    }
    return temp;
}

template <int r, int c>
matrix<r, c> operator-(const matrix<r, c> &mat1, const matrix<r, c> &mat2) {
    matrix<r, c> temp;
    for (int i = 0; i < r; i++) {
      temp[i] = mat1[i] - mat2[i];
    }
    return temp;
}

template <int r, int c>
matrix<r, c> operator*(const double &num, const matrix<r, c> &mat) {
    matrix<r, c> result;
    for (int i = 0; i < r; i++) {
      result[i] = num * mat[i];
    }
    return result;
}

template <int r, int c>
matrix<r, c> operator/(const matrix<r, c> &mat, const double &num) {
    matrix<r, c> result;
    for (int i = 0; i < r; i++) {
      result[i] = mat[i] / num;
    }
    return result;
}

template <int r, int c>
vec<r> operator*(const matrix<r, c> &mat, const vec<c> &v) {
    vec<r> result;
    for (int i = 0; i < r; i++) {
      result[i] = mat[i] * v;
    }
    return result;
}

template <int r, int t, int c>
matrix<r, c> operator*(const matrix<r, t> &mat1, const matrix<t, c> &mat2) {       //矩阵乘法
    matrix<r, c> result;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        result[i][j] = mat1[i] * mat2.getcolumn(j);
      }
    }
    return result;
}

template <int n> matrix<n, n> inverse(matrix<n, n> origin) {
    matrix<n, 2 * n> expand;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        expand[i][j] = origin[i][j];
        expand[i][j+n] = (i==j);
      }
    }

    for (int j = 0; j < n; j++) {
      int pivot = j;
      for (int i = j + 1; i < n; i++) {          //从当前行遍历行，找出本列主元(该列绝对值最大的数)的下标，并保证之前列已排好的主元位置不变
        if (std::abs(expand[i][j]) > std::abs(expand[pivot][j]))
          pivot = i;
      }
      std::swap(expand[j], expand[pivot]);    // 将主元放在对角线位置

      assert(std::abs(expand[j][j]) > 1e-10);     //判断矩阵是否可逆，若主元接近0，则该列元素皆接近0，行列式约等于0

      double pivot_value = expand[j][j];
      for (int i = 0; i < 2*n; i++) {
        expand[j][i] /= pivot_value;
      }

      for (int i = 0; i < n; i++) {
        if (i != j) {
          double value = expand[i][j];
          for (int k = 0; k < 2 * n; k++) {
            expand[i][k] -= value * expand[j][k];
          }
        }
      }
    }

    matrix<n, n> result;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        result[i][j] = expand[i][j + n];
      }
    }

    return result;
}