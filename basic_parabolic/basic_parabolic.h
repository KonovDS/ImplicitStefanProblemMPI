#ifndef IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_
#define IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_

#include "mpi_mesh.h"

class BasicParabolic {
  MPIMesh<double> before, after;
  double a, tau, h_x, h_y;

  double (*left)(size_t j);
  double (*right)(size_t j);
  double (*top)(size_t global_i);
  double (*bottom)(size_t global_i);

  void ExplicitScheme(size_t i, size_t j) {
    after.At(i, j) = before.At(i, j) + a * tau *
        (before.At(i - 1, j) - 2 * before.At(i, j) + before.At(i + 1, j))
        / (h_x * h_x) + a * tau *
        (before.At(i, j - 1) - 2 * before.At(i, j) + before.At(i, j + 1))
        / (h_y * h_y);
  }

  void Step() {
    for (size_t i = 1; i < before.DimK() - 1; i++) {
      for (size_t j = 1; j < before.DimL() - 1; j++) {
        ExplicitScheme(i, j);
      }
    }
    after.Update();
    std::swap(before, after);
    Border();
  }

  static double AutoTau(double h, double a) {
    return h * h / (2 * a);
  }

  void Compute(size_t steps) {
    for (size_t i = 0; i < steps; i++) {
      Step();
    }
  }

  void SetupInitial(double (*f)(size_t global_i, size_t j)) {
    for (size_t i = 0; i < before.DimK(); i++) {
      for (size_t j = 0; j < before.DimL(); j++) {
        before.At(i, j) = f(before.GlobalI(i), j);
      }
    }
  }

  void Border() {
    if (before.IsLeftBorder()) {
      for (size_t j = 0; j < before.DimL(); j++) {
        before.LeftPtrRecv()[j] = left(j);
      }
    }
    for (size_t i = 0; i < before.DimK(); i++) {
      before.At(i, 0) = top(before.GlobalI(i));
    }
    for (size_t i = 0; i < before.DimK(); i++) {
      before.At(i, before.DimL() - 1) = bottom(before.GlobalI(i));
    }
    if (before.IsRightBorder()) {
      for (size_t j = 0; j < before.DimL(); j++) {
        before.RightPtrRecv()[j] = right(j);
      }
    }
  }

 public:
  //BasicParabolic(size_t individual_k, size_t l);
};

#endif //IMPLICITSTEFANPROBLEMMPI_BASIC_PARABOLIC_BASIC_PARABOLIC_H_
