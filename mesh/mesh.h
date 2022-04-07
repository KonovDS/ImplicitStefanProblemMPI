#ifndef IMPLICITSTEFANPROBLEMMPI_MESH_MESH_H_
#define IMPLICITSTEFANPROBLEMMPI_MESH_MESH_H_
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

  T &At(size_t k, size_t l) {
    return data[k * dim_l + l];
  }

  T *LeftPtrRecv() {
    return &At(0, 0);
  }

  T *LeftPtrSend() {
    return &At(1, 0);
  }

  T *RightPtrRecv() {
    return &At(dim_k - 1, 0);
  }

  T *RightPtrSend() {
    return &At(dim_k - 2, 0);
  }

  size_t BorderLen() const {
    return dim_l;
  }
};

#endif //IMPLICITSTEFANPROBLEMMPI_MESH_MESH_H_