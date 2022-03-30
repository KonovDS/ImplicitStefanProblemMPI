#pragma once
#include <iostream>

#include <vector>

template <class T>
class Mesh {
  size_t dim_k, dim_l;
  std::vector<T> data;
 public:
  Mesh(size_t k, size_t l) : data(k*l), dim_k(k), dim_l(l) {}
  Mesh(const Mesh &rhs) = default;
  Mesh(Mesh &&rhs) noexcept = default;
  Mesh &operator=(const Mesh &rhs) = default;
  Mesh &operator=(Mesh &&rhs) noexcept = default;
  Mesh() = delete;

  T &at(size_t k, size_t l) {
    return data[k * dim_l + l];
  }

  T *LeftPtrRecv() {
    return &(data[0]);
  }

  T *LeftPtrSend() {
    return &(data[dim_l]);
  }

  T *RightPtrRecv() {
    return &(data[(dim_k - 1) * dim_l]);
  }

  T *RightPtrSend() {
    return &(data[(dim_k - 2) * dim_l]);
  }

  size_t BorderLen() const {
    return dim_l;
  }
};