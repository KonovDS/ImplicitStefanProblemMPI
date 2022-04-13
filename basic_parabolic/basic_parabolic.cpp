#include "basic_parabolic.h"

#include <omp.h>

void BasicParabolic::ExplicitScheme(size_t i, size_t j) {
  after.At(i, j) = before.At(i, j) + a * tau *
      (before.At(i - 1, j) - 2 * before.At(i, j) + before.At(i + 1, j))
      / (h_x * h_x) + a * tau *
      (before.At(i, j - 1) - 2 * before.At(i, j) + before.At(i, j + 1))
      / (h_y * h_y);
}

void BasicParabolic::Step() {
  Border();
#pragma omp parallel for default(none)
  for (size_t i = 1; i < before.DimK() - 1; i++) {
    for (size_t j = 1; j < before.DimL() - 1; j++) {
      ExplicitScheme(i, j);
    }
  }
  after.Update();
  std::swap(before, after);
}

void BasicParabolic::Compute(size_t steps) {
  for (size_t i = 0; i < steps; i++) {
    Step();
  }
}

void BasicParabolic::Border() {
  if (before.IsLeftBorder()) {
    for (size_t j = 0; j < before.DimL(); j++) {
      before.LeftPtrRecv()[j] = borders.l(j, before);
    }
  }
  for (size_t i = 0; i < before.DimK(); i++) {
    before.At(i, 0) = borders.t(before.GlobalI(i), before);
  }
  for (size_t i = 0; i < before.DimK(); i++) {
    before.At(i, before.DimL() - 1) = borders.b(before.GlobalI(i), before);
  }
  if (before.IsRightBorder()) {
    for (size_t j = 0; j < before.DimL(); j++) {
      before.RightPtrRecv()[j] = borders.r(j, before);
    }
  }
}

void BasicParabolic::Run(double t) {
  if (tau == 0) {
    throw IncompleteTask();
  }
  if (borders.l == nullptr || borders.r == nullptr || borders.t == nullptr || borders.b == nullptr) {
    throw IncompleteTask();
  }
  Compute(std::ceil(t / tau));
}

void BasicParabolic::Run(size_t s) {
  if (tau == 0) {
    throw IncompleteTask();
  }
  if (borders.l == nullptr || borders.r == nullptr || borders.t == nullptr || borders.b == nullptr) {
    throw IncompleteTask();
  }
  Compute(s);
}

double BasicParabolic::SetupTau(double t) {
  if (t == 0) {
    tau = AutoTau(std::min(h_x, h_y), a);
  } else {
    tau = t;
  }
  return tau;
}

void BasicParabolic::SetupInitial(double (*init)(size_t global_i, size_t j)) {
  for (size_t i = 0; i < before.DimK(); i++) {
    for (size_t j = 0; j < before.DimL(); j++) {
      before.At(i, j) = init(before.GlobalI(i), j);
    }
  }
}

double BasicParabolic::L2Partial(double (*f)(size_t global_i, size_t j)) {
  double res = 0;
  for (size_t i = 0; i < before.DimK(); i++) {
    for (size_t j = 0; j < before.DimL(); j++) {
      res += (before.At(i, j) - f(before.GlobalI(i), j)) * (before.At(i, j) - f(before.GlobalI(i), j));
    }
  }
  return res;
}

double BasicParabolic::L0Partial(double (*f)(size_t global_i, size_t j)) {
  double res = 0;
  for (size_t i = 0; i < before.DimK(); i++) {
    for (size_t j = 0; j < before.DimL(); j++) {
      auto c = std::abs(before.At(i, j) - f(before.GlobalI(i), j));
      if (res < c) {
        res = c;
      }
    }
  }
  return res;
}

// TODO
void PrintOut() {
  //std::vector<std::vector<double>> v(MPI_)
}